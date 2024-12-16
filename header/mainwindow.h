#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#define _USE_MATH_DEFINES

#include <QMainWindow>
#include "VirtuoseAPI.h"
#include "robot.h"
#include <iostream>
#include <QTimer>
#include <fstream>
#include <iomanip>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void main_loop();
    void gui_loop();
    void set_follow();
    void set_identifiate();
    void set_ylim();

private:

    /* METHODES */
    void read_system_state();
    void get_data();
    void write_data_header();
    void log_data();
    void update_panel();
    void update_data();
    void update_figure();
    void draw_robot_o();
    void draw_robot_t();
    void draw_ylim();

    void follow_command();
    void identification_command();

    /* ATTRIBUTS */
    Ui::MainWindow *_ui;

    float _sampling_ms;

    RobotHaption *_robot_o;
    RobotHaption *_robot_t;

    float _robot_o_q[2];
    float _robot_o_pos[2];
    float _robot_o_speed[2];
    float _cmd_o_q[2];
    float _cmd_o_torque[2];
    Eigen::Matrix2d _robot_o_J;

    float _robot_t_q[2];
    float _robot_t_pos[2];
    float _robot_t_speed[2];
    float _cmd_t_q[2];
    float _cmd_t_torque[2];
    Eigen::Matrix2d _robot_t_J;

    int _robot_o_deadman;
    int _robot_t_deadman;

    float _ylim;

    QTimer _main_loop_timer;
    QTimer _gui_loop_timer;

    bool _system_OK;
    bool _follow;
    bool _identifiate;
    bool _wall;

    std::ofstream _output_file;

    int _count;
};

#endif // MAINWINDOW_H
