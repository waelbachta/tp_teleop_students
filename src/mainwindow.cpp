#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    _ui(new Ui::MainWindow),
   // _robot_o(new RobotHaption("17", "127.0.0.1#5017", "C:\\Program Files\\HAPTION\\Haptic\\eduForce_n17\\v6.0.0600\\win64\\")),   // operateur
    _robot_o(new RobotHaption("18", "127.0.0.1#5018", "C:\\Program Files\\HAPTION\\Haptic\\eduForce_n18\\v6.0.0600\\win64\\")),   // operateur
    _robot_t(new RobotHaption("19", "127.0.0.1#5019", "C:\\Program Files\\HAPTION\\Haptic\\eduForce_n19\\v6.0.0600\\win64\\")),   // teleopere
    _system_OK(false),
    _follow(false),
    _identifiate(false),
    _wall(false),
    _count(0)
{
    /* FENETRE GRAPHIQUE */
    _ui->setupUi(this);
    setWindowTitle("PUPITRE EDUFORCE");

    /* INITIALISATION ATTRIBUTS */
    _sampling_ms = 5.0;

    _ylim = _ui->teleop_ylim->value()*0.001;    // [m]

    _robot_o_q[0] = 0.0;        // [rad]
    _robot_o_q[1] = 0.0;

    _robot_o_pos[0] = 0.0;      // [m]
    _robot_o_pos[1] = 0.0;

    _robot_o_speed[0] = 0.0;    // [m/s]
    _robot_o_speed[1] = 0.0;

    _cmd_o_q[0] = 0.0;          // [m/s]
    _cmd_o_q[1] = 0.0;

    _cmd_o_torque[0] = 0.0;     // [N.m]
    _cmd_o_torque[1] = 0.0;    

    _robot_t_q[0] = 0.0;        // [rad]
    _robot_t_q[1] = 0.0;

    _robot_t_pos[0] = 0.0;      // [m]
    _robot_t_pos[1] = 0.0;

    _robot_t_speed[0] = 0.0;
    _robot_t_speed[1] = 0.0;

    _cmd_t_q[0] = 0.0;          // [m/s]
    _cmd_t_q[1] = 0.0;

    _cmd_t_torque[0] = 0.0;     // [N.m]
    _cmd_t_torque[1] = 0.0;

    _robot_o_deadman = 0;
    _robot_t_deadman = 0;


    /* COMPORTEMENT DE L'INTERFACE */

        /* Robot opérateur */
        connect(_ui->Ro_bouton_demarrer,SIGNAL(clicked(bool)),_robot_o,SLOT(restart()));
        connect(_ui->Ro_bouton_calibrer,SIGNAL(clicked(bool)),_robot_o,SLOT(calibrate()));
        connect(_ui->Ro_bouton_connecter,SIGNAL(clicked(bool)),_robot_o,SLOT(connect()));

        /* Robot teleopéré */
        connect(_ui->Rt_bouton_demarrer,SIGNAL(clicked(bool)),_robot_t,SLOT(restart()));
        connect(_ui->Rt_bouton_calibrer,SIGNAL(clicked(bool)),_robot_t,SLOT(calibrate()));
        connect(_ui->Rt_bouton_connecter,SIGNAL(clicked(bool)),_robot_t,SLOT(connect()));

        /* Système de téléopération */
        connect(_ui->teleop_bouton_lancer,SIGNAL(clicked(bool)),this,SLOT(set_follow()));
        connect(_ui->teleop_ylim,SIGNAL(valueChanged(double)),this,SLOT(set_ylim()));
        connect(_ui->teleop_bouton_identifier,SIGNAL(clicked(bool)),this,SLOT(set_identifiate()));


    /* FIGURE */

        /* MISE EN FORME */
        _ui->figure->xAxis->setLabel("y [mm]");
        _ui->figure->yAxis->setLabel("x [mm]");
        _ui->figure->xAxis->setRange(-400, 0);
        _ui->figure->yAxis->setRange(0, 400);

        /* GRAPHES */

            /* 0: robot_o */
            _ui->figure->addGraph();
            _ui->figure->graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssDisc,QPen(QColor(255,127,0)),Qt::SolidPattern,5));

            /* 1: robot_t */
            _ui->figure->addGraph();
            _ui->figure->graph(1)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssDisc,QPen(QColor(50,150,150)),Qt::SolidPattern,5));

            /* 2: ylim */
            _ui->figure->addGraph();
            _ui->figure->graph(2)->setPen(QPen(Qt::red));

    /* TIMERS */
    connect(&_main_loop_timer,SIGNAL(timeout()),this,SLOT(main_loop()));
    connect(&_gui_loop_timer,SIGNAL(timeout()),this,SLOT(gui_loop()));

    _main_loop_timer.start(_sampling_ms);   // periode en [ms]
    _gui_loop_timer.start(100);
}

MainWindow::~MainWindow()
{
    _output_file.close();
    delete _robot_o;
    delete _robot_t;
    delete _ui;
}


/*
 * SLOTS
 */

/* BOUCLES DE COMMANDE ET D'AFFICHAGE */

void MainWindow::main_loop()
{
    read_system_state();
    get_data();
    log_data();

    if (_robot_o->isConnected() && _robot_t->isConnected())
    {
        if (_follow)
            follow_command();

        if (_identifiate)
            identification_command();
    }
    _count++;
}


void MainWindow::gui_loop()
{
    update_panel();
    update_data();
    update_figure();
}


/* CHANGEMENTS D'ETAT */

void MainWindow::set_ylim()
{
    _ylim = _ui->teleop_ylim->value()*0.001;    // [m]
}

void MainWindow::set_follow()
{
    _follow = !_follow;
    _count = 0;

    // on ferme le fichier lors de l'arret de la teleoperation
    if (!_follow)
    {
        _output_file.close();
        _robot_o->power(false); // important pour pouvoir utiliser la securite homme-mort
        _robot_t->power(false);
        _robot_o->disconnect();
        _robot_t->disconnect();
        _system_OK = false;
    }

    // on ouvre un nouveau fichier lors du demarrage de la teleoperation
    if (_follow)
    {
        remove("log/output_file.txt");
        _output_file.open("log/output_file.txt",std::ios::app);
        write_data_header();
        _robot_o->power(true); // important pour pouvoir utiliser la securite homme-mort
        _robot_t->power(true);
    }
}

void MainWindow::set_identifiate()
{
    _identifiate = !_identifiate;
    _count = 0;

    // on ferme le fichier lors de l'arret de l'identification
    if (!_identifiate)
    {
        _output_file.close();
        _robot_o->power(false); // important pour pouvoir utiliser la securite homme-mort
        _robot_t->power(false);
        _robot_o->disconnect();
        _robot_t->disconnect();
        _system_OK = false;
    }

    // on ouvre un nouveau fichier lors du demarrage de l'identification
    if (_identifiate)
    {
        remove("log/output_file.txt");
        _output_file.open("log/output_file.txt",std::ios::app);
        write_data_header();
        _robot_o->power(true); // important pour pouvoir utiliser la securite homme-mort
        _robot_t->power(true);
    }
}


/*
 * METHODES PRIVEES
 */

void MainWindow::read_system_state()
{
    /* ROBOT OPERATEUR */
    if (_robot_o->isConnected())
    {
        _robot_o->readPhysicalArticularPosition();
        _robot_o->readPhysicalPosition(); //operationnel
        _robot_o->readPhysicalSpeed(); //operationnel
        _robot_o->updateJacobian();
        _robot_o->readPhysicalDeadMan();
    }

    /* ROBOT TELEOPERE */
    if (_robot_t->isConnected())
    {
        _robot_t->readPhysicalArticularPosition();
        _robot_t->readPhysicalPosition();
        _robot_t->readPhysicalSpeed();
        _robot_t->updateJacobian();
        _robot_t->readPhysicalDeadMan();
    }
}

void MainWindow::get_data()
{
    /* ROBOT OPERATEUR */
    _robot_o->getPosArti(_robot_o_q);
    _robot_o->getPosCart(_robot_o_pos);
    _robot_o->getSpeedCart(_robot_o_speed);
    _robot_o->getJacobian(_robot_o_J);
    _robot_o->getDeadMan(_robot_o_deadman);

    /* ROBOT TELEOPERE */
    _robot_t->getPosArti(_robot_t_q);
    _robot_t->getPosCart(_robot_t_pos);
    _robot_t->getSpeedCart(_robot_t_speed);
    _robot_t->getJacobian(_robot_t_J);
    _robot_t->getDeadMan(_robot_t_deadman);
}


void MainWindow::write_data_header()
{
    _output_file << "Temps [ms]\t";
    _output_file << "Robot Operateur q1 [rad]\t" << "Robot Operateur q2 [rad]\t";
    _output_file << "Robot Teleopere q1 [rad]\t" << "Robot Teleopere q2 [rad]\t";
    _output_file << "Robot Operateur x [m]\t" << "Robot Operateur y [m]\t";
    _output_file << "Robot Teleopere x [m]\t" << "Robot Teleopere y [m]\t";
    _output_file << "Commande Operateur q1 [rad]\t" << "Commande Operateur q2 [rad]\t";
    _output_file << "Deadman\t";
    _output_file << "\n";
}


void MainWindow::log_data()
{
    if (_output_file.is_open())
    {
        _output_file << std::setprecision(3) << _count*_sampling_ms << "\t";
        _output_file << std::setprecision(3) << _robot_o_q[0] <<"\t" << _robot_o_q[1] <<"\t";
        _output_file << std::setprecision(3) << _robot_t_q[0] <<"\t" << _robot_t_q[1] <<"\t";
        _output_file << std::setprecision(3) << _robot_o_pos[0] <<"\t" << _robot_o_pos[1] <<"\t";
        _output_file << std::setprecision(3) << _robot_t_pos[0] <<"\t" << _robot_t_pos[1] <<"\t";
        _output_file << std::setprecision(3) << _cmd_o_q[0] <<"\t" << _cmd_o_q[1] <<"\t";
        _output_file << _robot_o_deadman << "\n";
        _output_file << "\n";
    }
}


void MainWindow::update_panel()
{
    // on change l'etat de systeme_OK lorsque les deux robots sont connectes
    if (!_system_OK && _robot_o->isConnected() && _robot_t->isConnected())
    {
        _system_OK = true;
    }

    // lorsque le systeme est OK, on peut utiliser les boutons qui lancent la teleop ou l'identification
    if (_system_OK)
    {
        _ui->teleop_bouton_lancer->setEnabled(true);
        _ui->teleop_bouton_identifier->setEnabled(true);
    }
    else
    {
        _ui->teleop_bouton_lancer->setEnabled(false);
        _ui->teleop_bouton_identifier->setEnabled(false);
    }

    // on desactive le bouton identifier lors de la teleop
    if (_follow)
        _ui->teleop_bouton_identifier->setEnabled(false);

    // on desactive le bouton teleop lors de l'identification
    if (_identifiate)
        _ui->teleop_bouton_lancer->setEnabled(false);

    // on recupere l'etat de la checkbox du mur
    _wall = _ui->teleop_box_ylim->isChecked();
}

void MainWindow::update_data()
{
    /* ROBOT OPERATEUR */
    _ui->Ro_q1->setText(QString::number(_robot_o_q[0]));
    _ui->Ro_q2->setText(QString::number(_robot_o_q[1]));
    _ui->Ro_x->setText(QString::number(_robot_o_pos[0]*1000));  // affichage en [mm]
    _ui->Ro_y->setText(QString::number(_robot_o_pos[1]*1000));

    /* ROBOT TELEOPERE */
    _ui->Rt_q1->setText(QString::number(_robot_t_q[0]));
    _ui->Rt_q2->setText(QString::number(_robot_t_q[1]));
    _ui->Rt_x->setText(QString::number(_robot_t_pos[0]*1000));  // affichage en [mm]
    _ui->Rt_y->setText(QString::number(_robot_t_pos[1]*1000));
}

void MainWindow::update_figure()
{
    draw_robot_o();
    draw_robot_t();
    draw_ylim();
    _ui->figure->replot();
}

void MainWindow::draw_robot_o()
{
    QVector<double> x(1), y(1);
    x[0] = _robot_o_pos[0]*1000;    // affichage en [mm]
    y[0] = _robot_o_pos[1]*1000;    // affichage en [mm]
    _ui->figure->graph(0)->setData(y, x);
}

void MainWindow::draw_robot_t()
{
    QVector<double> x(1), y(1);
    x[0] = _robot_t_pos[0]*1000;    // affichage en [mm]
    y[0] = _robot_t_pos[1]*1000;    // affichage en [mm]
    _ui->figure->graph(1)->setData(y, x);
}

void MainWindow::draw_ylim()
{
    QVector<double> x(2), y(2);
    x[0] = 0;
    x[1] = 400;
    y[0] = _ylim*1000;      // [mm]
    y[1] = _ylim*1000;      // [mm]
    _ui->figure->graph(2)->setData(y, x);
}


/* CONTROLEUR */

void MainWindow::follow_command()
{
    // ------------------------------------
    // VARIABLES
    // ------------------------------------

    // controleur
    float kr_t, kv_t, kr_o, kv_o;
    float fx_t, fy_t, fx_o, fy_o;
    float kr_mur;
    float kv_mur;

    // consignes d'effort
    Eigen::Vector2d force_t, force_o, torque_t, torque_o;
    float torqueCmd_t[2], torqueCmd_o[2];

    // Gains proportionnel et dérivé du robot teleopere
    /**** Remplir ***/
    kr_t = 0.0;
    kv_t = 0.0;

    // Gains proportionnel et dérivé  du robot operateur

    kr_o = kr_t;
    kv_o = kv_t;

    //raideur et frottement visqueux mur virtuel

    kr_mur = 400.0;
    kv_mur = 3.0;

    float e_pos_x = this->_robot_o_pos[0] - this->_robot_t_pos[0];
    float e_pos_y = this->_robot_o_pos[1] - this->_robot_t_pos[1];
    float e_speed_x = this->_robot_o_speed[0] - this->_robot_t_speed[0];
    float e_speed_y = this->_robot_o_speed[1] - this->_robot_t_speed[1];

    // ------------------------------------
    // ROBOT TELEOPERE SUIT ROBOT OPERATEUR
    // ------------------------------------

    // Le mur est coché et le robot teleopere rentre dans le mur ou en sort
    if(_wall && (_robot_t_pos[1] > _ylim)  )
    {
        // suivi en x normal car le mur est selon y

        // Remplir

        fx_t = 0.0;

        // Le robot teleopere suit l'operateur mais subit l'effort du mur virtuel
        // Calcul erreur par rapport au mur

        // Remplir

        float e_mur_y =  0.0;
        float e_mur_speed_y = 0.0;

        // si robot teleopere rentre dans le mur (raideur + viscositÃ©)
        if (this->_robot_t_speed[1] > 0.0)

            // Remplir

            fy_t = 0.0;

        // si robot teleopere sort du mur (raideur)
        if (this->_robot_t_speed[1] < 0.0)

            //Remplir

            fy_t = 0.0;
    }


    // Le mur est coché et le robot teleopere est loin du mur : suivi classique
    if( _wall && (_robot_t_pos[1] < _ylim) ){
        
        // Remplir //

          fx_t = 0.0;
          fy_t = 0.0;

    }


    // Le mur n'est pas coché : suivi classique
    if(!_wall)
    {
        /************ Remplir *************/
        fx_t = 0.0;
        fy_t = 0.0;

    }

    force_t << fx_t, fy_t;

    // on projette ces efforts dans l'espace articulaire pour determiner les consignes de couple
    torque_t = _robot_t_J.transpose() * force_t;

    torqueCmd_t[0] = torque_t[0];
    torqueCmd_t[1] = torque_t[1];

    if (this->_robot_o_deadman!=1)  // si on appuie l'interrupteur homme-mort du robot opérateur, le robot téléopéré n'est pas actionné
    {
        torqueCmd_t[0] = 0.0;
        torqueCmd_t[1] = 0.0;
    }

    _robot_t->setTorqueCmd(torqueCmd_t);


    // ------------------------------------
    // ROBOT OPERATEUR SUIT ROBOT TELEOPERE
    // ------------------------------------



    // effort dans l'espace operationnel

    /************ Remplir *************/
    // force à  appliquer selon l'axe x
    fx_o = 0.0;

    // force à  appliquer selon l'axe y
    fy_o = 0.0;

    force_o << fx_o, fy_o;

    // on projette ces efforts dans l'espace articulaire pour determiner les consignes de couple
    torque_o = _robot_o_J.transpose() * force_o;

    torqueCmd_o[0] = torque_o[0];
    torqueCmd_o[1] = torque_o[1];

    _robot_o->setTorqueCmd(torqueCmd_o);
}




/* IDENTIFICATION DU SYSTEME */

void MainWindow::identification_command()
{

    // ------------------------------------
    // VARIABLES
    // ------------------------------------

    // controleur
    float kr_t, kv_t, kr_o, kv_o;
    float fx_t, fy_t, fx_o, fy_o;

    // consignes d'effort
    Eigen::Vector2d force_t, force_o, torque_t, torque_o;
    float torqueCmd_t[2], torqueCmd_o[2];

    // sinusoide
    float A, fe, f, d_fh;


    // ON AJOUTE UNE SINUSOIDE Simulant un effort de l'utilisateur
    f = 0.1;    // [Hz] frÃ©quence de la sinusoide
    fe = 1.0/(_sampling_ms*0.001); // [Hz] frÃ©quence d'Ã©chantillonnage
    A = 0.8;   // [N] amplitude

    d_fh = A*sin(2*M_PI*_count*f/fe);


    // SAISIR : Gains proportionnel et dérivé du robot teleopere

    // Modifier
    kr_t = 0.0;
    kv_t = 0.0;

    // Gains proportionnel et dérivé du robot operateur
    kr_o = kr_t;
    kv_o = kv_t;

    // ------------------------------------
    // ROBOT TELEOPERE SUIT ROBOT OPERATEUR
    // ------------------------------------


    // effort dans l'espace operationnel

    // Ecrire la compsante de la force opérationnelle à  appliquer à  l'organe terminal
    // du robot téléopéré pour qu'il suive le robot opérateur
    //  _robot_o_pos[0] / _robot_t_pos[0] : postion selon x de l'OT du robot opérateur / teleopere
    // _robot_o_speed[0] / _robot_t_speed[0] : vitesse selon x de l'OT du robot opérateur / teleopere
    //  _robot_o_pos[1] / _robot_t_pos[1] : postion selon y de l'OT du robot opérateur / teleopere
    // _robot_o_speed[1] / _robot_t_speed[1] : vitesse selon y de l'OT du robot opérateur / teleopere
    // Les gains des correcteur sont Ã  saisir plus haut

    float e_pos_x = this->_robot_o_pos[0] - this->_robot_t_pos[0];
    float e_pos_y = this->_robot_o_pos[1] - this->_robot_t_pos[1];
    float e_speed_x = this->_robot_o_speed[0] - this->_robot_t_speed[0];
    float e_speed_y = this->_robot_o_speed[1] - this->_robot_t_speed[1];

    // force à  appliquer selon l'axe x
    // Modifier
    fx_t = 0.0;

    // force à  appliquer selon l'axe y
    // Modifier
    fy_t = 0.0;

    force_t << fx_t, fy_t;

    // on projette ces efforts dans l'espace articulaire pour determiner les consignes de couple
    torque_t = _robot_t_J.transpose() * force_t;

    torqueCmd_t[0] = torque_t[0];
    torqueCmd_t[1] = torque_t[1];

    if (this->_robot_o_deadman!=1)  // si on appuie l'interrupteur homme-mort du robot opérateur, le robot téléopéré n'est pas actionné
    {
        torqueCmd_t[0] = 0.0;
        torqueCmd_t[1] = 0.0;
    }

    _robot_t->setTorqueCmd(torqueCmd_t);


    // ------------------------------------
    // ROBOT OPERATEUR SUIT ROBOT TELEOPERE
    // ------------------------------------

    // effort dans l'espace operationnel

    // Ecrire la compsante de la force opÃ©rationnelle Ã  appliquer Ã  l'organe terminal
    // du robot opérateur pour qu'il suive le robot téléopéré
    //  _robot_o_pos[0] / _robot_t_pos[0] : postion selon x de l'OT du robot opérateur / teleopere
    // _robot_o_speed[0] / _robot_t_speed[0] : vitesse selon x de l'OT du robot opérateur / teleopere
    //  _robot_o_pos[1] / _robot_t_pos[1] : postion selon y de l'OT du robot opérateur / teleopere
    // _robot_o_speed[1] / _robot_t_speed[1] : vitesse selon y de l'OT du robot opérateur / teleopere

    // Une fois la téléopération validée : vous pourrez ajouter à  l'une ou l'autre des composantes d_fh

    // Les gains des correcteur sont à  saisir plus haut

    // force à  appliquer selon l'axe x
    // Modifier
    fx_o = 0.0;

    // force à appliquer selon l'axe x
    // Modifier
    fy_o = 0.0;

    //fx_o += d_fh;
    //fy_o += d_fh;

    force_o << fx_o, fy_o;

    // on projette ces efforts dans l'espace articulaire pour determiner les consignes de couple
    torque_o = _robot_o_J.transpose() * force_o;

    torqueCmd_o[0] = torque_o[0];
    torqueCmd_o[1] = torque_o[1];

    _robot_o->setTorqueCmd(torqueCmd_o);
}

