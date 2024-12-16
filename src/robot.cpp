#include "robot.h"

#include <iostream>
#include <math.h>

#include <QSettings>
#include <QProcess>

#include <sstream>

using namespace std;
using namespace Eigen;


/* CONSTRUCTEUR */
RobotHaption::RobotHaption(QString id, QString ip, QString haption_path)
{
    m_id = id;
    m_ip = ip;
    m_haption_path = haption_path;
    m_connected = false;
    m_powered = false;

    m_FSaturation_total = 5.0;

    m_l1 = 0.25;    // longueur du bras 1 [m]
    m_l2 = 0.25;    // longueur du bras 2 [m]

    for(int i=0; i<2; i++)
    {
        m_force_de_commande[i] = 0.0f;
        m_pos_arti[i] = 0.0f;
        m_pos_cart[i] = 0.0f;
        m_origin_arti[i] = 0.0f;
        m_origin_cart[i] = 0.0f;
        m_speed_cart[i] = 0.0f;
    }
}

/* DESTRUCTEUR */

RobotHaption::~RobotHaption()
{
}

/*
 * METHODES PUBLIQUES
 */


/* COMMUNICATION */
bool RobotHaption::isConnected(void)
{
    return m_connected;
}


void RobotHaption::closeCommunication()
{
    stopHaptionService();
}

/* ETAT DU ROBOT */
void RobotHaption::readPhysicalArticularPosition(void)
{
    float pos_arti[2];
    m_communication_status = virtGetArticularPosition(m_VC, pos_arti);
    m_pos_arti[0] = pos_arti[0];// - m_origin_arti[0];
    m_pos_arti[1] = pos_arti[1];// - m_origin_arti[1];
}


void RobotHaption::readPhysicalSpeed(void)
{
    float pos_speed[6];
    m_communication_status = virtGetPhysicalSpeed(m_VC, pos_speed);
    m_speed_cart[0] = pos_speed[0];
    m_speed_cart[1] = pos_speed[1];
}


void RobotHaption::readPhysicalPosition(void)
{
    float pos_cart[7];
    m_communication_status = virtGetPhysicalPosition(m_VC, pos_cart);
    m_pos_cart[0] = pos_cart[0] - m_origin_cart[0];
    m_pos_cart[1] = pos_cart[1] - m_origin_cart[1];
}


int RobotHaption::updatePhysicalParameters()
{
    int send_status = -1;

    if(limitForce(m_force_de_commande))
    {
        send_status = 0;
    }

    if(isNumber(m_force_de_commande,2))
    {
        m_communication_status = virtSetForce(m_VC, m_force_de_commande);
        send_status = 1;
    }
    else
    {
        for(int i=0; i<2; i++)
        {
            m_force_de_commande[i] = 0.0f;
        }
        m_communication_status = virtSetForce(m_VC, m_force_de_commande);

        send_status = 2;
    }

    return send_status;
}


int RobotHaption::readPhysicalDeadMan(void)
{
    return virtGetDeadMan(m_VC, &m_deadman);
}


QString RobotHaption::printMainInfos()
{
    QString ret;
    ret += " pos_arti ";
    for(int i=0; i<2; i++)
        ret += QString::number(m_pos_arti[i]) + " ";
    ret += " force ";
    for(int i=0; i<2; i++)
        ret += QString::number(m_force_de_commande[i]) + " ";
    ret += " pos_cart ";
    for(int i=0; i<3; i++)
        ret += QString::number(m_pos_cart[i]) + " ";

    return ret;
}


/* ACCESSEURS */

int RobotHaption::readVariableCommunicationStatus(void)
{
    return m_communication_status;
}

void RobotHaption::getPosArti(float posArti[2])
{
    posArti[0] = m_pos_arti[0];
    posArti[1] = m_pos_arti[1];
}

void RobotHaption::getPosCart(float posCart[2])
{
    posCart[0] = m_pos_cart[0];
    posCart[1] = m_pos_cart[1];
}

void RobotHaption::getSpeedCart(float speedCart[2])
{
    speedCart[0] = m_speed_cart[0];
    speedCart[1] = m_speed_cart[1];
}

void RobotHaption::getJacobian(Matrix2d& jacobian)
{
    jacobian(0,0) = m_jacobian(0,0);
    jacobian(0,1) = m_jacobian(0,1);
    jacobian(1,0) = m_jacobian(1,0);
    jacobian(1,1) = m_jacobian(1,1);
}

Matrix2d RobotHaption::getJacobianPinv()
{
    return m_jacobian_pinv;
}

void RobotHaption::getDeadMan(int& deadman)
{
    deadman = m_deadman;
}

bool RobotHaption::isPowered(void)
{
    return m_powered;
}



/* CONSIGNES */

int RobotHaption::setArticularPositionCmd(float pos_arti[2])
{
    m_communication_status = virtSetArticularPosition(m_VC, pos_arti);
    return m_communication_status;
}

int RobotHaption::setTorqueCmd(float forceCmd[2])
{
    m_communication_status = virtSetArticularForce(m_VC, forceCmd);
    return m_communication_status;
}

int RobotHaption::setArticularSpeedCmd(float speedCmd[2])
{
    m_communication_status = virtSetArticularSpeed(m_VC, speedCmd);
    return m_communication_status;
}

void RobotHaption::setForceCmd(float forceCmd[2])
{
    for(int i=0;i<2;i++)
    {
        m_force_de_commande[i] = forceCmd[i];
    }
}



/*
 * MODELES GEOMETRIQUES ET CINEMATIQUES
 */

/* CALCUL DU MODELE GEOMETRIQUE DIRECT */
// q1, q2 relatifs
int RobotHaption::mgd(const float q[2], float pos[2])
{
    float q1 = q[0];    // [rad]
    float q2 = q[1];    // [rad]

    pos[0] = m_l1*cos(q1)+m_l2*cos(q1+q2);
    pos[1] = m_l1*sin(q1)+m_l2*sin(q1+q2);

    return 0;
}

/* CALCUL DU MODELE GEOMETRIQUE INVERSE */
int RobotHaption::mgi(const float pos[2], float q[2])
{
    float x = pos[0];   // [m]
    float y = pos[1];   // [m]

    // pour que acos ait une solution, en realite il faudrait une condition plus restrictive sur la zone de travail du robot.
    if ( (pow(x,2)+pow(y,2))>=pow((m_l1-m_l2),2) && (pow(x,2)+pow(y,2))<=pow((m_l1+m_l2),2) )
    {
        float alpha, beta, gamma;
        alpha = -acos(((pow(x,2)+pow(y,2))-(pow(m_l1,2)+pow(m_l2,2)))/(2*m_l1*m_l2));   // alpha est toujours negatif
        beta = atan2(m_l2*sin(alpha), m_l1+m_l2*cos(alpha));
        gamma = atan2(y, x);

        q[0] = gamma-beta;
        q[1] = alpha;

        return 0;
    }

    // en dehors de la zone d'action, pas de solution au modele
    else
    {
        return -1;
    }
}

/* CALCUL DE LA MATRICE JACOBIENNE dX/dQ */
void RobotHaption::updateJacobian()
{
    // matrices
    Matrix2d J, Jt, I2, Jinv;

    // configuration articulaire du robot
    float q1 = m_pos_arti[0];
    float q2 = m_pos_arti[1];

    /* Termes de la jacobienne : derivees partielles dxi/dqi */
    J(0,0) = - m_l1*sin(q1) - m_l2*sin(q1+q2);
    J(0,1) = - m_l2*sin(q1+q2);
    J(1,0) = m_l1*cos(q1) + m_l2*cos(q1+q2);
    J(1,1) = m_l2*cos(q1+q2);

    m_jacobian = J;


    /* Jacobienne pseudo-inverse */
    Jt = J.transpose();
    I2 = Matrix2d::Identity();
    Jinv = J.inverse();

    m_jacobian_pinv = Jt * (J * Jt + 0.01 * I2).inverse();

}




/*
 * SLOTS
 */

void RobotHaption::restart()
{
    stopHaptionService();
    startHaptionService();
}


void RobotHaption::calibrate()
{
    execCalibration();
}

void RobotHaption::power(bool on)
{
    int status;

    if(!this->isConnected())
        return;
    if(on){
        status = virtSetPowerOn(m_VC,1);
        if (status == 0)
        {
            m_powered = true;
            cout<<"power ON"<<endl;
        }
        else
        {
            cerr << "Erreur dans virtSetPowerOn : " << virtGetErrorMessage(virtGetErrorCode(NULL)) << endl;
        }

    }
    else{
        status = virtSetPowerOn(m_VC,0);
        if (status == 0)
        {
            m_powered = false;
            cout<<"power OFF"<<endl;
        }
        else
        {
            cerr << "Erreur dans virtSetPowerOn : " << virtGetErrorMessage(virtGetErrorCode(NULL)) << endl;
        }
    }
}

void RobotHaption::connect()
{
    cout<< m_ip.toStdString() << endl;
    m_VC = virtOpen(m_ip.toStdString().c_str());
    cout<<m_VC<<endl;

    if(m_VC != NULL)
    {
        init();
        m_connected = true;
        m_button = 0;
        std::cout<<"Robot connected"<<std::endl;
    }
    else
    {
        cerr << "Erreur dans virtOpen : " << virtGetErrorMessage(virtGetErrorCode(NULL)) << endl;

        m_connected = false;
    }
}


void RobotHaption::disconnect()
{
    m_connected = false;
    /*
    if( virtClose(m_VC) == 0 )
        m_connected = false;
    else
        cout<<"Erreur de deconnexion du robot."<<endl;
    */
}


void RobotHaption::init()
{
    virtSetIndexingMode(m_VC,INDEXING_ALL); // permet de gerer le decalage entre robot et mecanisme virtuel lorsque la puissance est OFF
    virtSetForceFactor(m_VC, 1.0f);
    virtSetSpeedFactor(m_VC, 1.0f);
    virtSetTimeStep(m_VC, 0.005f); // !!!

    float identity[7]={0.0f , 0.0f , 0.0f , 0.0f , 0.0f , 0.0f , 1.0f};
    virtSetBaseFrame(m_VC, identity);
    virtSetObservationFrame(m_VC, identity);
    virtSetObservationFrameSpeed(m_VC, identity);

    virtSetCommandType(m_VC, COMMAND_TYPE_ARTICULAR_IMPEDANCE);
}


/*
 * METHODES PRIVEES
 */

bool RobotHaption::limitForce(float commande[2])
{
    float norme;

    norme = sqrt( commande[0]*commande[0]+commande[1]*commande[1] );

    m_FSaturation_total = (m_FSaturation_total>0 ? m_FSaturation_total : -m_FSaturation_total); // au cas où l'utilisateur met une fmax négative

    if (norme <= m_FSaturation_total)
    {
        m_force_de_commande[0] = commande[0];
        m_force_de_commande[1] = commande[1];

        return false;
    }
    else
    {
        cout << "Efforts trop importants, saturation effective." << endl;
        m_force_de_commande[0] = commande[0]*m_FSaturation_total/norme;
        m_force_de_commande[1] = commande[1]*m_FSaturation_total/norme;

        return true;
    }

    return false;
}

void RobotHaption::startHaptionService()
{
    QProcess process;
    process.start("\""+m_haption_path + "start_service_eduForce_n"+m_id+".bat\"");
    process.waitForFinished(-1);
    std::cout<<"Service du robot N"<<m_id.toStdString().c_str()<<" demarre."<<std::endl;
}

void RobotHaption::stopHaptionService()
{
    QProcess process;
    process.start("\""+m_haption_path + "stop_service_eduForce_n"+m_id+".bat\"");
    process.waitForFinished(-1);
    std::cout<<"Service du robot N"<<m_id.toStdString().c_str()<<" arrete."<<std::endl;
}

void RobotHaption::execCalibration()
{
    QString cmd = "start cmd /k \""+m_haption_path + "calibration_eduForce_n"+m_id+".exe\"";
    std::cout<< cmd.toStdString().c_str() << std::endl;
    system(cmd.toStdString().c_str());
}

bool RobotHaption::isNumber(float* number, unsigned int size)
{
    if(size == 0)
        return false;

    ostringstream os;
    if(size == 1)
    {
        os << number[0];
        if(os.str().find('#') != -1)
            return false;
        os.clear();
    }
    else
    {
        for(unsigned int i=0; i<size; i++)
        {
            os << number[i];
            if(os.str().find('#') != -1)
            {
                return false;
            }
            os.clear();
        }
    }
    return true;
}



