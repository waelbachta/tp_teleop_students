#ifndef ROBOT_H
#define ROBOT_H

#include <QObject>
#include "virtuoseAPI.h"
#include <QString>
#include <Eigen/Dense>

class RobotHaption: public QObject
{
    Q_OBJECT

public:

    /**
     * @brief Demarre le service haption, se connecte au robot via l'adresse
     *        IP donnee dans robot.ini, initialise l'impedance du robot.
     */
    RobotHaption(QString id, QString ip, QString haption_path);
    ~RobotHaption();

    /**
     * @brief   Renvoie l'etat de connexion du robot.
     * @return    vrai si le robot est connecte au pc, faux sinon.
     */
    bool isConnected(void);

    /**
     * @brief   Ferme la connexion entre le robot et le pc en appelant
     *           virtClose() puis arrete le service Haption.
     */
    void closeCommunication();

    /**
     * @brief   Appelle la fonction virtGetPhysicalPosition() et remplit la
     *          variable \a m_pos_orientation_6_dans_0.
     */
    void readPhysicalPosition(void);

    void readPhysicalSpeed(void);

    /**
     * @brief   Appelle la fonction virtGetArticularPosition() et remplit la
     *          variable \a m_position_arti.
     */
    void readPhysicalArticularPosition(void);


    /**
     * @brief   Recupere l'etat de la pedale via la fonction virtGetButton()
     *          et remplit la variable \a m_pedale.
     */
    void readPhysicalButton(void);
    /**
     * @brief   Retourne la valeur de la pedale.
     * @return   \a m_pedale.
     */
    int readVariableButton(void);

    /**
     * @brief   Donne l'etat de la commnication entre le robot et le pc.
     * @return  La variable \a m_communication_status, -1 = probleme.
     */
    int readVariableCommunicationStatus(void);

    /**
     * @brief   Envoie au robot la commande des freins et appelle la
     *          fonction virtSetForce(), avant cet appel la methode ajoute
     *          dans la force de commande la compensation du poids de la
     *          sonde, ensuite limite cette force de commande et enfin avant
     *          d'envoyer au robot teste si la force envoyee est bien un
     *          un nombre.
     * @return  0 si la force a due Ãªtre limitee.
     * @return  2 si la force n'etait pas un nombre.
     * @return  -1 si pas de problÃ¨mes.
     */
    int updatePhysicalParameters();

    /**
     * @brief   Retourne une chaine de caractères contenant les informations
     *          principale du robot, cette chaine peut ensuite être affichée
     *          ou écrite dans un fichier.
     */

    int readPhysicalDeadMan(void);
    bool isPowered(void);

    QString printMainInfos();

    void getPosArti(float[2]);
    void getPosCart(float[2]);
    void getSpeedCart(float[2]);
    void getJacobian(Eigen::Matrix2d&);
    Eigen::Matrix2d getJacobianPinv();
    void getDeadMan(int&);

    void setForceCmd(float[2]);
    int setArticularPositionCmd(float [2]);
    int setTorqueCmd(float [2]);
    int setArticularSpeedCmd(float [2]);

    float m_origin_arti[2];
    Eigen::Matrix2d m_jacobian;

    void updateJacobian();
    int mgd(const float q[2], float pos[2]);
    int mgi(const float pos[2], float q[2]);


public slots:
    void restart();
    void calibrate();
    void connect();
    void disconnect();
    void init();
    void power(bool);


private:

    /* ATTRIBUTS */

    VirtContext m_VC;
    bool m_connected;
    bool m_powered;

    QString m_haption_path;

    float m_FSaturation_total;

    QString m_id;
    QString m_ip;

    float m_l1;     // longueur du bras 1
    float m_l2;     // longueur du bras 2

    int m_powerstatus;
    int m_communication_status;
    float m_force_de_commande[2];

    int m_button;
    int m_deadman;

    float m_pos_cart[7];
    float m_pos_arti[2];
    float m_origin_cart[2];
    float m_speed_cart[2];

    Eigen::Matrix2d m_jacobian_pinv;


    /* METHODES PRIVEES */

    /**
     * @brief   Limite la force de commande donnee Ã  \a m_FSaturation_total.
     *
     * @return  vrai si la force a due Ãªtre limitee, faux sinon.
     */
    bool limitForce(float commande[6]);

    /**
     * @brief   Demarre le service Haption en executant le fichier
     *          start_service_v3d15_25n8.bat.
     */
    void startHaptionService();

    /**
     * @brief   ArrÃªte le service Haption en executant le fichier
     *          stop_service_v3d15_25n8.bat.
     */
    void stopHaptionService();

    void execCalibration();

    bool isNumber(float* number, unsigned int size);

};

#endif // ROBOT_H
