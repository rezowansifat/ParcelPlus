#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QUrlQuery>
#include <QMessageBox>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_stackedWidget_currentChanged(int arg1)
{

}

void MainWindow::on_get_started_home_clicked()
{
  ui->stackedWidget->setCurrentIndex(1);
}


void MainWindow::on_sl_admin_pushButton_1_clicked()
{
  ui->stackedWidget->setCurrentIndex(2);
}


void MainWindow::on_sl_user_pushButton_2_clicked()
{
  ui->stackedWidget->setCurrentIndex(4);
}


void MainWindow::on_al_pushButton_goto_login_clicked()
{
  ui->stackedWidget->setCurrentIndex(5);
}


void MainWindow::on_ur_pushButton_goto_login_clicked()
{
    ui->stackedWidget->setCurrentIndex(4);
}


void MainWindow::on_backpush_clicked()
{
    int previousIndex = ui->stackedWidget->currentIndex() - 1;
    if (previousIndex < 0) {
        previousIndex = ui->stackedWidget->count() - 1;
    }
    ui->stackedWidget->setCurrentIndex(previousIndex);
}


void MainWindow::on_backpushTosl_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

//Slot function for registration (user admin db)
void MainWindow::on_ur_pushButton_userReg_clicked()
{
    // Disable button
    ui->ur_pushButton_userReg->setEnabled(false);

    // user inputs
    QString name = ui->ur_lineEdit_name->text();
    QString email = ui->ur_lineEdit_email->text();
    QString password = ui->ur_lineEdit_pass->text();

    // Creating a object with the user data
    QJsonObject userObject;
    userObject["name"] = name;
    userObject["email"] = email;
    userObject["password"] = password;
    userObject["role "] = "user";

    //Object to a string
    QJsonDocument jsonDoc(userObject);
    QByteArray jsonData = jsonDoc.toJson();

    //POST request to databse
    QNetworkAccessManager* networkManager = new QNetworkAccessManager(this);
    connect(networkManager, &QNetworkAccessManager::finished, this, [=](QNetworkReply* reply) {
        // Enable button
        ui->ur_pushButton_userReg->setEnabled(true);

        if (reply->error() == QNetworkReply::NoError) {
            qDebug() << "User registered successfully!";
            ui->stackedWidget->setCurrentIndex(4);
        } else {
            qDebug() << "Failed to register user:" << reply->errorString();
            QMessageBox::critical(this, "Error", "Failed to register user: " + reply->errorString());
        }
        reply->deleteLater();
    });

    QUrl url("https://parcelplus-25cc2-default-rtdb.firebaseio.com/users.json");
    QUrlQuery urlQuery;
    urlQuery.addQueryItem("auth", "53gKbnYDUOuvyuQNmf72svwvvSyjtUCVhWGiWVmg");
    url.setQuery(urlQuery);

    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    networkManager->post(request, jsonData);
}

//Slot function for user and db login
void MainWindow::on_al_pushButton_admin_login_2_clicked()
{
    //Button Disable
    ui->al_pushButton_admin_login_2->setEnabled(false);

    // Getting the email and password
    QString email = ui->al_lineEdit_email_2->text();
    QString password = ui->al_lineEdit_pass_2->text();

    //GET request to database
    QNetworkAccessManager* networkManager = new QNetworkAccessManager(this);
    connect(networkManager, &QNetworkAccessManager::finished, this, [=](QNetworkReply* reply) {
        // Enable button
        ui->al_pushButton_admin_login_2->setEnabled(true);

        if (reply->error() == QNetworkReply::NoError) {
            // Get data from the reply
            QByteArray jsonData = reply->readAll();
            QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonData);
            QJsonObject jsonObj = jsonDoc.object();

            // User with the entered email exists and the password match
            bool userExists = false;

            for (const auto& user : jsonObj) {
                QJsonObject userObj = user.toObject();
                if (userObj.value("email").toString() == email) {
                    userExists = true;
                    if (userObj.value("password").toString() == password) {
                         QString role = userObj["role "].toString();

                        if (role == "db") {
                                ui->stackedWidget->setCurrentIndex(7);

                            QString name = userObj["name"].toString();
                            QString userEmail = userObj["email"].toString();

                            //setting the user's name and email
                            ui->usernamelabel_2->setText(name);
                            ui->useremaillabel_2->setText(userEmail);

                            userEmailAddress = userEmail;
                        } else{
                            ui->stackedWidget->setCurrentIndex(6);
                                // getting the user's name and email
                            QString name = userObj["name"].toString();
                            QString userEmail = userObj["email"].toString();

                                //setting the user's name and email
                                ui->usernamelabel->setText(name);
                                ui->useremaillabel->setText(userEmail);
                                ui->ap_lineEdit_name->setText(name);
                                ui->ap_lineEdit_email->setText(userEmail);
                                userEmailAddress = userEmail;

                                 qDebug() <<name;
                                qDebug() <<userEmail;
                        }
                    } else {
                        // Wrong password
                        QMessageBox::critical(this, "Error", "Wrong Password");
                        break;
                    }
                }
            }
            if (!userExists) {
                // User not found
                QMessageBox::critical(this, "Error", "User Not Found");
            }
        } else {
            // Error occurred
            qDebug() << "Error:" << reply->errorString();
            QMessageBox::critical(this, "Error", "Failed To Fetch Data From Database: " + reply->errorString());
        }
        reply->deleteLater();
    });

    QUrl url("https://parcelplus-25cc2-default-rtdb.firebaseio.com/users.json");
    QUrlQuery urlQuery;
    urlQuery.addQueryItem("print", "pretty");
    url.setQuery(urlQuery);

    QNetworkRequest request(url);

    networkManager->get(request);
}

//Slot function for Admin login
void MainWindow::on_al_pushButton_admin_login_clicked()
{
    //Button Disable
    ui->al_pushButton_admin_login->setEnabled(false);

    // Getting the email and password
    QString email = ui->al_lineEdit_email->text();
    QString password = ui->al_lineEdit_pass->text();

    //GET request to database
    QNetworkAccessManager* networkManager = new QNetworkAccessManager(this);
    connect(networkManager, &QNetworkAccessManager::finished, this, [=](QNetworkReply* reply) {
        // Enable button
        ui->al_pushButton_admin_login->setEnabled(true);

        if (reply->error() == QNetworkReply::NoError) {
            // Get data from the reply
            QByteArray jsonData = reply->readAll();
            QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonData);
            QJsonObject jsonObj = jsonDoc.object();

            // User with the entered email exists and the password match
            bool userExists = false;
            for (const auto& user : jsonObj) {
                QJsonObject userObj = user.toObject();
                if (userObj.value("email").toString() == email) {
                    userExists = true;
                    if (userObj.value("password").toString() == password) {
                        QString role = userObj["role "].toString();
                        if (role == "admin") {
                            ui->stackedWidget->setCurrentIndex(8);


                            QString name = userObj["name"].toString();
                            QString userEmail = userObj["email"].toString();

                            ui->adminhome_name_label->setText(name);
                            ui->adminhome_email_label->setText(userEmail);
                        } else{
                            // Wrong password
                            QMessageBox::critical(this, "Error", "Access Denied : Not An Admin Account");
                            break;
                        }
                    } else {
                        // Wrong password
                        QMessageBox::critical(this, "Error", "Wrong Password");
                        break;
                    }
                }
            }
            if (!userExists) {
                // User not found
                QMessageBox::critical(this, "Error", "User Not Found");
            }
        } else {
            // Error occurred
            qDebug() << "Error:" << reply->errorString();
            QMessageBox::critical(this, "Error", "Failed To Fetch Data From Database: " + reply->errorString());
        }
        reply->deleteLater();
    });

    QUrl url("https://parcelplus-25cc2-default-rtdb.firebaseio.com/users.json");
    QUrlQuery urlQuery;
    urlQuery.addQueryItem("print", "pretty");
    url.setQuery(urlQuery);

    QNetworkRequest request(url);

    networkManager->get(request);
}

void MainWindow::on_userlogut_clicked()
{
    ui->stackedWidget->setCurrentIndex(5);
}



//Add Percele
void MainWindow::on_ap_pushButton_add_clicked()
{
    // Disable button
    ui->ap_pushButton_add->setEnabled(false);

    // user inputs
    QString name = ui->ap_lineEdit_name->text();
    QString reciverName = ui->ap_lineEdit_reciverName->text();
    QString email = ui->ap_lineEdit_email->text();
    QString mobile = ui->ap_lineEdit_mobile->text();
    QString receiverMobile = ui->ap_lineEdit_receiverMobile->text();
    QString address = ui->ap_lineEdit_address->text();
    QString destination = ui->ap_destination_comboBox->currentText();
    QString type = ui->ap_type_comboBox->currentText();
    QString status = "pending";
    QString costing;

    if (destination == "Inside Chittagong") {
        costing = "60";
    } else {
        costing = "120";
    }

    // Creating a object with the user data
    QJsonObject parcelObject;
    parcelObject["name"] = name;
    parcelObject["reciverName"] = reciverName;
    parcelObject["email"] = email;
    parcelObject["mobile"] = mobile;
    parcelObject["receiverMobile"] = receiverMobile;
    parcelObject["address"] = address;
    parcelObject["destination"] = destination;
    parcelObject["type"] = type;
    parcelObject["status"] = status;
    parcelObject["costing"] = costing;
    parcelObject["dbmail"] = "N/A";

    //Object to a string
    QJsonDocument jsonDoc(parcelObject);
    QByteArray jsonData = jsonDoc.toJson();

    //POST request to databse
    QNetworkAccessManager* networkManager = new QNetworkAccessManager(this);
    connect(networkManager, &QNetworkAccessManager::finished, this, [=](QNetworkReply* reply) {
        // Enable button
        ui->ap_pushButton_add->setEnabled(true);

        if (reply->error() == QNetworkReply::NoError) {
            qDebug() << "Parcel Added Successfully!";
            ui->stackedWidget->setCurrentIndex(6);
        } else {
            qDebug() << "Failed To Add Parcel:" << reply->errorString();
            QMessageBox::critical(this, "Error", "Failed To Add Parcel: " + reply->errorString());
        }
        reply->deleteLater();
    });

    QUrl url("https://parcelplus-25cc2-default-rtdb.firebaseio.com/parcels.json");
    QUrlQuery urlQuery;
    urlQuery.addQueryItem("auth", "53gKbnYDUOuvyuQNmf72svwvvSyjtUCVhWGiWVmg");
    url.setQuery(urlQuery);

    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    networkManager->post(request, jsonData);

}


void MainWindow::on_userlogut_2_clicked()
{
     ui->stackedWidget->setCurrentIndex(6);
}


void MainWindow::on_user_pushButton_goaddpercle_clicked()
{
    ui->stackedWidget->setCurrentIndex(9);
}


void MainWindow::on_myPercle_pushButton_clicked()
{

}

//USER MY PERCELS
void MainWindow::on_user_pushButton_addpercle_2_clicked()
{
    // Disable button
    ui->user_pushButton_addpercle_2->setEnabled(false);

    ui->stackedWidget->setCurrentIndex(10);

    // Get the user's email
    if (userEmailAddress.isEmpty()) {
        QMessageBox::critical(this, "Error", "User email not found.");
        return;
    }

    //GET request to retrieve parcels based on the user's email
    QNetworkAccessManager* networkManager = new QNetworkAccessManager(this);
    connect(networkManager, &QNetworkAccessManager::finished, this, [=](QNetworkReply* reply) {
        if (reply->error() == QNetworkReply::NoError) {

            ui->user_pushButton_addpercle_2->setEnabled(true);
            // Get data from the reply
            QByteArray jsonData = reply->readAll();
            QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonData);
            QJsonObject jsonObj = jsonDoc.object();

            // Loop through the parcels and display them
            for (const auto& parcel : jsonObj) {
                QJsonObject parcelObj = parcel.toObject();
                if (parcelObj.value("email").toString() == userEmailAddress) {
                    // Displaying parcel information
                    QString name = parcelObj["name"].toString();
                    QString email = parcelObj["email"].toString();
                    QString reciverName = parcelObj["reciverName"].toString();
                    QString mobile = parcelObj["mobile"].toString();
                    QString receiverMobile = parcelObj["receiverMobile"].toString();
                    QString address = parcelObj["address"].toString();
                    QString destination = parcelObj["destination"].toString();
                    QString type = parcelObj["type"].toString();
                    QString status = parcelObj["status"].toString();
                    QString costing = parcelObj["costing"].toString();

                    ui->pd_name_label->setText(name);
                    ui->pd_email_label->setText(email);
                    ui->pd_phone_label->setText(mobile);

                    ui->pd_sndr_name_label->setText(reciverName);
                    ui->pd_sndr_Destination_label->setText(destination);
                    ui->pd_sndr_phone_label->setText(receiverMobile);


                    ui->pd_type_label->setText(type);
                    ui->pd_costing_label->setText(costing);
                    ui->pd_status_label->setText(status);
                    ui->pd_address_label->setText(address);

                }
            }
        } else {
            qDebug() << "Failed To Fetch Parcels:" << reply->errorString();
            QMessageBox::critical(this, "Error", "Failed To Fetch Parcels: " + reply->errorString());
        }
        reply->deleteLater();
    });

    QUrl url("https://parcelplus-25cc2-default-rtdb.firebaseio.com/parcels.json");
    QUrlQuery urlQuery;
    urlQuery.addQueryItem("auth", "53gKbnYDUOuvyuQNmf72svwvvSyjtUCVhWGiWVmg");
    url.setQuery(urlQuery);

    QNetworkRequest request(url);

    networkManager->get(request);
}


void MainWindow::on_userlogut_5_clicked()
{
    ui->stackedWidget->setCurrentIndex(6);
}


void MainWindow::on_admin_logout_clicked()
{
    ui->stackedWidget->setCurrentIndex(5);
}


//Admin All Parcels
void MainWindow::on_user_pushButton_goaddpercle_3_clicked()
{
    ui->stackedWidget->setCurrentIndex(12);

    QNetworkAccessManager* networkManager = new QNetworkAccessManager(this);
    connect(networkManager, &QNetworkAccessManager::finished, this, [=](QNetworkReply* reply) {
        if (reply->error() == QNetworkReply::NoError) {
            // Getting Data
            QByteArray jsonData = reply->readAll();
            QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonData);
            QJsonObject jsonObj = jsonDoc.object();

            for (const auto& parcel : jsonObj) {
                QJsonObject parcelObj = parcel.toObject();

                // Displaying parcel information
                QString name = parcelObj["name"].toString();
                QString email = parcelObj["email"].toString();
                QString reciverName = parcelObj["reciverName"].toString();
                QString mobile = parcelObj["mobile"].toString();
                QString receiverMobile = parcelObj["receiverMobile"].toString();
                QString address = parcelObj["address"].toString();
                QString destination = parcelObj["destination"].toString();
                QString type = parcelObj["type"].toString();
                QString status = parcelObj["status"].toString();
                QString costing = parcelObj["costing"].toString();
                QString dbmail = parcelObj["dbmail"].toString();

                percleMail = email;

                ui->allp_name_label->setText(name);
                ui->allp_email_label->setText(email);
                ui->pd_phone_label_3->setText(mobile);
                ui->pd_sndr_name_label_3->setText(reciverName);
                ui->pd_sndr_Destination_label_3->setText(destination);
                ui->pd_sndr_phone_label_3->setText(receiverMobile);
                ui->pd_type_label_3->setText(type);
                ui->allp_costing_label_2->setText(costing);
                ui->pd_status_label_3->setText(status);
                ui->allp_address_label->setText(address);
                ui->allp_dbmail_label->setText(dbmail);
            }
        } else {
            qDebug() << "Failed To Fetch Parcels:" << reply->errorString();
            QMessageBox::critical(this, "Error", "Failed To Fetch Parcels: " + reply->errorString());
        }

        reply->deleteLater();
    });

    QUrl url("https://parcelplus-25cc2-default-rtdb.firebaseio.com/parcels.json");
    QUrlQuery urlQuery;
    urlQuery.addQueryItem("auth", "53gKbnYDUOuvyuQNmf72svwvvSyjtUCVhWGiWVmg");
    url.setQuery(urlQuery);

    QNetworkRequest request(url);
    networkManager->get(request);

    // Call the function to load DB users
    loadDbUsers();
}

// Loading DB users
void MainWindow::loadDbUsers()
{
    QNetworkAccessManager* networkManager = new QNetworkAccessManager(this);
    connect(networkManager, &QNetworkAccessManager::finished, this, [=](QNetworkReply* reply) {
        if (reply->error() == QNetworkReply::NoError) {
            QByteArray jsonData = reply->readAll();
            QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonData);
            QJsonObject jsonObj = jsonDoc.object();

            for (const auto& user : jsonObj) {
                QJsonObject userObj = user.toObject();
                QString email = userObj["email"].toString();
                QString role = userObj["role "].toString();

                qDebug() << role;
                 qDebug() << userObj;
                if (role == "db") {
                    ui->allp_db_select_comboBox->addItem(email);
                }
            }
        } else {
            qDebug() << "Failed to fetch users:" << reply->errorString();
            QMessageBox::critical(this, "Error", "Failed to fetch users: " + reply->errorString());
        }

        reply->deleteLater();
    });

    QUrl url("https://parcelplus-25cc2-default-rtdb.firebaseio.com/users.json");
    QUrlQuery urlQuery;
    urlQuery.addQueryItem("auth", "53gKbnYDUOuvyuQNmf72svwvvSyjtUCVhWGiWVmg");
    url.setQuery(urlQuery);

    QNetworkRequest request(url);
    networkManager->get(request);
}

//Adimn Assign Db
void MainWindow::on_allp_updatep_pushButton_clicked()
{
    QString selectedEmail = ui->allp_db_select_comboBox->currentText();

    //Finding the parcel with the  email
    QNetworkAccessManager* networkManager = new QNetworkAccessManager(this);
    connect(networkManager, &QNetworkAccessManager::finished, this, [=](QNetworkReply* reply) {
        if (reply->error() == QNetworkReply::NoError) {
            QByteArray jsonData = reply->readAll();
            QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonData);
            QJsonObject jsonObj = jsonDoc.object();

            bool parcelFound = false;
            QString parcelId;
            QJsonObject existingParcelData;
            for (auto it = jsonObj.constBegin(); it != jsonObj.constEnd(); ++it) {
                const QString& key = it.key();
                const QJsonValue& value = it.value();
                if (value.isObject()) {
                    const QJsonObject& parcelObj = value.toObject();
                    QString email = parcelObj["email"].toString();
                    if (email == percleMail) {
                        parcelFound = true;
                        parcelId = key;
                        existingParcelData = parcelObj;
                        break;
                    }
                }
            }

            if (parcelFound) {
                // Updating The dbmail
                existingParcelData["dbmail"] = selectedEmail;

                //PUT request
                QByteArray updateJsonData = QJsonDocument(existingParcelData).toJson();

                QNetworkAccessManager* updateManager = new QNetworkAccessManager(this);
                connect(updateManager, &QNetworkAccessManager::finished, this, [=](QNetworkReply* updateReply) {
                    if (updateReply->error() == QNetworkReply::NoError) {
                        qDebug() << "Parcel updated successfully";
                        ui->stackedWidget->setCurrentIndex(8);
                    } else {
                        qDebug() << "Failed to update parcel:" << updateReply->errorString();
                        QMessageBox::critical(this, "Error", "Failed to update parcel: " + updateReply->errorString());
                    }

                    updateReply->deleteLater();
                });

                QString updateUrlStr = "https://parcelplus-25cc2-default-rtdb.firebaseio.com/parcels/" + parcelId + ".json";
                QUrl updateUrl(updateUrlStr);
                QUrlQuery updateUrlQuery;
                updateUrlQuery.addQueryItem("auth", "53gKbnYDUOuvyuQNmf72svwvvSyjtUCVhWGiWVmg");
                updateUrl.setQuery(updateUrlQuery);

                QNetworkRequest updateRequest(updateUrl);
                updateRequest.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

                updateManager->put(updateRequest, updateJsonData);
            } else {
                qDebug() << "Parcel not found";
                QMessageBox::critical(this, "Error", "Parcel not found");
            }
        } else {
            qDebug() << "Failed to fetch parcels:" << reply->errorString();
            QMessageBox::critical(this, "Error", "Failed to fetch parcels: " + reply->errorString());
        }

        reply->deleteLater();
    });

    QString fetchUrlStr = "https://parcelplus-25cc2-default-rtdb.firebaseio.com/parcels.json";
    QUrl fetchUrl(fetchUrlStr);
    QUrlQuery fetchUrlQuery;
    fetchUrlQuery.addQueryItem("auth", "53gKbnYDUOuvyuQNmf72svwvvSyjtUCVhWGiWVmg");
    fetchUrl.setQuery(fetchUrlQuery);

    QNetworkRequest fetchRequest(fetchUrl);
    networkManager->get(fetchRequest);

}


void MainWindow::on_userlogut_9_clicked()
{
   ui->stackedWidget->setCurrentIndex(8);
}


void MainWindow::on_userlogut_3_clicked()
{
    ui->stackedWidget->setCurrentIndex(5);
}

//Parcel to dalevery
void MainWindow::on_user_pushButton_addpercle_3_clicked()
{
     ui->stackedWidget->setCurrentIndex(11);

    QNetworkAccessManager* networkManager = new QNetworkAccessManager(this);
    connect(networkManager, &QNetworkAccessManager::finished, this, [=](QNetworkReply* reply) {
        if (reply->error() == QNetworkReply::NoError) {
            QByteArray jsonData = reply->readAll();
            QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonData);
            QJsonObject jsonObj = jsonDoc.object();

            // Find the parcel with the given email
            QJsonObject parcelObj;
            for (const auto& parcel : jsonObj) {
                QJsonObject currentParcelObj = parcel.toObject();
                QString email = currentParcelObj["email"].toString();

                if (email == userEmailAddress) {
                    parcelObj = currentParcelObj;
                    break;
                }
            }

            // Check if the parcel was found
            if (!parcelObj.isEmpty()) {
                // Display parcel information
                QString name = parcelObj["name"].toString();
                QString email = parcelObj["email"].toString();
                QString reciverName = parcelObj["reciverName"].toString();
                QString mobile = parcelObj["mobile"].toString();
                QString receiverMobile = parcelObj["receiverMobile"].toString();
                QString address = parcelObj["address"].toString();
                QString destination = parcelObj["destination"].toString();
                QString type = parcelObj["type"].toString();
                QString status = parcelObj["status"].toString();
                QString costing = parcelObj["costing"].toString();
                QString dbmail = parcelObj["dbmail"].toString();

                percleMail = email;

                ui->allp_name_label_6->setText(name);
                ui->allp_email_label_2->setText(email);
                ui->pd_phone_label_4->setText(mobile);
                ui->pd_sndr_name_label_4->setText(reciverName);
                ui->pd_sndr_Destination_label_4->setText(destination);
                ui->pd_sndr_phone_label_4->setText(receiverMobile);
                ui->pd_type_label_4->setText(type);
                ui->allp_costing_label_3->setText(costing);
                ui->pd_status_label_4->setText(status);
                ui->allp_address_label_2->setText(address);
                ui->allp_dbmail_label_2->setText(dbmail);
            } else {

            }
        } else {

        }
        reply->deleteLater();
    });

    QUrl url("https://parcelplus-25cc2-default-rtdb.firebaseio.com/parcels.json");
    QUrlQuery urlQuery;
    urlQuery.addQueryItem("auth", "53gKbnYDUOuvyuQNmf72svwvvSyjtUCVhWGiWVmg");
    url.setQuery(urlQuery);

    QNetworkRequest request(url);
    networkManager->get(request);
}


void MainWindow::on_userlogut_10_clicked()
{
     ui->stackedWidget->setCurrentIndex(7);
}

