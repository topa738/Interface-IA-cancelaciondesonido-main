    #include "mainwindow.h"
    #include "./ui_mainwindow.h"
    #include <QDebug>
    #include <portaudio.h>
    #include <QProcess>

    MainWindow::MainWindow(QWidget *parent)
        : QMainWindow(parent)
        , ui(new Ui::MainWindow)
    {
        ui->setupUi(this);
        // Conectar los botones a los slots
        connect(ui->pushButton, &QPushButton::clicked, this, &MainWindow::on_button1_clicked);
        connect(ui->pushButton_2, &QPushButton::clicked, this, &MainWindow::on_button2_clicked);
        connect(ui->checkBox, &QCheckBox::toggled, this, &MainWindow::onCheckBoxToggled);
        connect(ui->checkBox_3, &QCheckBox::toggled, this, &MainWindow::onCheckBoxToggled);

        // Rellenar los QComboBox
        fillComboBoxes();
        fillComboBoxes2();

       // listAudioDevices();
    }
    // En el constructor de MainWindow





    MainWindow::~MainWindow()
    {
        delete ui;
    }
    void MainWindow::on_button1_clicked()
    {
        // Aquí va la funcionalidad del botón 1
        fillComboBoxes();
        qDebug() << "Recarga los dispositivos";
    }
   void MainWindow::fillComboBoxes2()
    {
        // Rellenar el primer QComboBox
        ui->comboBox->addItem("1 leve");
        ui->comboBox->addItem("2 medio");
        ui->comboBox->addItem("3 Alto");


    }
    void MainWindow::fillComboBoxes()
    {
        PaError err = Pa_Initialize();
        if (err != paNoError) {
            qDebug() << "PortAudio error: " << Pa_GetErrorText(err);
            return;
        }

        int numDevices = Pa_GetDeviceCount();
        if (numDevices < 0) {
            qDebug() << "PortAudio error: " << Pa_GetErrorText(numDevices);
            Pa_Terminate();
            return;
        }

        ui->comboBox_3->clear(); // Limpiar el ComboBox para dispositivos de salida
        ui->comboBox_2->clear(); // Limpiar el ComboBox para dispositivos de entrada

        for (int i = 0; i < numDevices; ++i) {
            const PaDeviceInfo *deviceInfo = Pa_GetDeviceInfo(i);
            if (deviceInfo) {
                QString deviceName = QString::fromUtf8(deviceInfo->name);

                // Filtrar dispositivos para entrada y salida

                    ui->comboBox_3->addItem(deviceName); // Agregar dispositivo de entrada
                    ui->comboBox_2->addItem(deviceName); // Agregar dispositivo de salida

            }
        }

        Pa_Terminate();
    }
    void MainWindow::getSelectedValues()
    {
        int selectedComboBoxValue = ui->comboBox->currentIndex() + 1;  // Aumenta agresividad de voz
        int selectedComboBoxValue2 = ui->comboBox_2->currentIndex();   // Dispositivo de entrada
        int selectedComboBoxValue3 = ui->comboBox_3->currentIndex();   // Dispositivo de salida
        bool checkBoxState = ui->checkBox->isChecked();                // Activador de IA
        bool checkBoxState2 = ui->checkBox_2->isChecked();             // Activador de voz
        bool checkBoxState3 = ui->checkBox_3->isChecked();            //Activar libreria
        qDebug() << "IA Activada: " << (checkBoxState ? "Sí" : "No");
        qDebug() << "VAD Activado: " << (checkBoxState2 ? "Sí" : "No");
         QString program = "python3";  // O "python" si es correcto en tu sistema
        QStringList arguments;

        // Detener cualquier proceso en ejecución antes de iniciar uno nuevo
        if (process.state() == QProcess::Running) {
            process.terminate();
            process.waitForFinished();
        }
        if(checkBoxState3){
            // Configurar el comando y sus argumentos
            arguments << "/home/facu/Escritorio/repos/IA-cancelacion-de-ruido-/uso_argumentosNR.py"
                      << QString::number(selectedComboBoxValue)
                      << QString::number(selectedComboBoxValue2)
                      << QString::number(selectedComboBoxValue3)
                      << (checkBoxState ? "True" : "False")
                      << (checkBoxState2 ? "True" : "False");

        }else{
            // Configurar el comando y sus argumentos
           arguments << "/home/facu/IA-interface/uso_argumentos.py"
                      << QString::number(selectedComboBoxValue)
                      << QString::number(selectedComboBoxValue2)
                      << QString::number(selectedComboBoxValue3)
                      << (checkBoxState ? "True" : "False")
                      << (checkBoxState2 ? "True" : "False");

        }

        // Conectar las señales para capturar la salida en tiempo real
        connect(&process, &QProcess::readyReadStandardOutput, this, [&]() {
            QString output = process.readAllStandardOutput();
            qDebug() << "Output:" << output;
        });
        connect(&process, &QProcess::readyReadStandardError, this, [&]() {
            QString error = process.readAllStandardError();
            qDebug() << "Error:" << error;
        });

        // Iniciar el proceso
        process.start(program, arguments);

        if (!process.waitForStarted()) {
            qDebug() << "Error al iniciar el proceso";
        }
    }
    // Slot que gestiona el estado de los checkboxes
    void MainWindow::onCheckBoxToggled(bool checked)
    {
        QCheckBox *senderCheckBox = qobject_cast<QCheckBox *>(sender());
        if (senderCheckBox == ui->checkBox) {
            // Si checkBox_1 es activado, desactiva checkBox_2
            if (checked) {
                ui->checkBox_3->setChecked(false);
            }
        } else if (senderCheckBox == ui->checkBox_3) {
            // Si checkBox_2 es activado, desactiva checkBox_1
            if (checked) {
                ui->checkBox->setChecked(false);
            }
        }
    }


    void MainWindow::on_button2_clicked()
    {
        // Aquí va la funcionalidad del botón 2
        getSelectedValues();
    }
