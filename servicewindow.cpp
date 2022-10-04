#include "servicewindow.h"
#include "ui_servicewindow.h"

servicewindow::servicewindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::servicewindow)
{
    ui->setupUi(this);
    QPixmap pix("C:/DEG/index.png");
    ui->Logo_label->setPixmap(pix);

    clr_red.setColor(QPalette::Base,Qt::red);
    clr_green.setColor(QPalette::Base,Qt::green);
    clr_banana.setColor(QPalette::Base,Qt::yellow);
    clr_white.setColor(QPalette::Base,Qt::white);
    tmrS = new QTimer(this); // Создаем объект класса QTimer и передаем адрес переменной
    tmrS->setInterval(1000); // Задаем интервал таймера
    connect(tmrS, SIGNAL(timeout()), this, SLOT(timeout())); // Подключаем сигнал таймера к нашему слоту
    tmrS->start(); // Запускаем таймер

    csvModel = new QStandardItemModel(this);
    csvModel->setColumnCount(4);
    csvModel->setHorizontalHeaderLabels(QStringList() << "ВРЕМЯ" << "" << "" << "" << "СООБЩЕНИЕ");
    ui->tableView->setModel(csvModel); // Устанавливаем модель в таблицу
    ui->tableView->setColumnWidth(0,150);
    ui->tableView->setColumnWidth(1,0);
    ui->tableView->setColumnWidth(2,0);
    ui->tableView->setColumnWidth(3,0);
    ui->tableView->setColumnWidth(4,580);
     ui->tableView->setColumnWidth(5,0);
}

servicewindow::~servicewindow()
{
    delete ui;
}

void servicewindow::timeout(){
    ui->time_label->setText(QTime::currentTime().toString());
    QDate now = QDate::currentDate();
    if (QTime::currentTime().secsTo(QTime(00,00,01)) == 0)
    {
        ui->calendarWidget->setSelectedDate(now);
    }
}
void servicewindow::opened(){

    this->show();
    showFullScreen();
}

void servicewindow::get(int rc)
{
    if( rc== -1){ui->listView_connect->setPalette(clr_red);}
    else { ui->listView_connect->setPalette(clr_green);}
}
void servicewindow::bvv_in(bvv_DI par1)
{
//-------------------BVV1---------------------------
if (par1.bvv_DI_1 & (1 << 0)){ui->listView->setPalette(clr_banana);}
else{ui->listView->setPalette(clr_white);}
if (par1.bvv_DI_1 & (1 << 1)){ui->listView_2->setPalette(clr_banana);}
else{ui->listView_2->setPalette(clr_white);}
if (par1.bvv_DI_1 & (1 << 2)){ui->listView_3->setPalette(clr_banana);}
else{ui->listView_3->setPalette(clr_white);}
if (par1.bvv_DI_1 & (1 << 3)){ui->listView_4->setPalette(clr_banana);}
else{ui->listView_4->setPalette(clr_white);}
if (par1.bvv_DI_1 & (1 << 4)){ui->listView_5->setPalette(clr_banana);}
else{ui->listView_5->setPalette(clr_white);}
if (par1.bvv_DI_1 & (1 << 5)){ui->listView_6->setPalette(clr_banana);}
else{ui->listView_6->setPalette(clr_white);}
if (par1.bvv_DI_1 & (1 << 6)){ui->listView_7->setPalette(clr_banana);}
else{ui->listView_7->setPalette(clr_white);}
if (par1.bvv_DI_1 & (1 << 7)){ui->listView_8->setPalette(clr_banana);}
else{ui->listView_8->setPalette(clr_white);}
if (par1.bvv_DI_1 & (1 << 8)){ui->listView_9->setPalette(clr_banana);}
else{ui->listView_9->setPalette(clr_white);}
if (par1.bvv_DI_1 & (1 << 9)){ui->listView_10->setPalette(clr_banana);}
else{ui->listView_10->setPalette(clr_white);}
if (par1.bvv_DI_1 & (1 << 10)){ui->listView_11->setPalette(clr_banana);}
else{ui->listView_11->setPalette(clr_white);}
if (par1.bvv_DI_1 & (1 << 11)){ui->listView_12->setPalette(clr_banana);}
else{ui->listView_12->setPalette(clr_white);}
if (par1.bvv_DI_1 & (1 << 12)){ui->listView_13->setPalette(clr_banana);}
else{ui->listView_13->setPalette(clr_white);}
if (par1.bvv_DI_1 & (1 << 13)){ui->listView_14->setPalette(clr_banana);}
else{ui->listView_14->setPalette(clr_white);}
if (par1.bvv_DI_1 & (1 << 14)){ui->listView_15->setPalette(clr_banana);}
else{ui->listView_15->setPalette(clr_white);}
if (par1.bvv_DI_1 & (1 << 15)){ui->listView_16->setPalette(clr_banana);}
else{ui->listView_16->setPalette(clr_white);}

//-------------------BVV2---------------------------
if (par1.bvv_DI_2 & (1 << 0)){ui->listView_33->setPalette(clr_banana);}
else{ui->listView_33->setPalette(clr_white);}
if (par1.bvv_DI_2 & (1 << 1)){ui->listView_34->setPalette(clr_banana);}
else{ui->listView_34->setPalette(clr_white);}
if (par1.bvv_DI_2 & (1 << 2)){ui->listView_35->setPalette(clr_banana);}
else{ui->listView_35->setPalette(clr_white);}
if (par1.bvv_DI_2 & (1 << 3)){ui->listView_36->setPalette(clr_banana);}
else{ui->listView_36->setPalette(clr_white);}
if (par1.bvv_DI_2 & (1 << 4)){ui->listView_37->setPalette(clr_banana);}
else{ui->listView_37->setPalette(clr_white);}
if (par1.bvv_DI_2 & (1 << 5)){ui->listView_38->setPalette(clr_banana);}
else{ui->listView_38->setPalette(clr_white);}
if (par1.bvv_DI_2 & (1 << 6)){ui->listView_39->setPalette(clr_banana);}
else{ui->listView_39->setPalette(clr_white);}
if (par1.bvv_DI_2 & (1 << 7)){ui->listView_40->setPalette(clr_banana);}
else{ui->listView_40->setPalette(clr_white);}
if (par1.bvv_DI_2 & (1 << 8)){ui->listView_41->setPalette(clr_banana);}
else{ui->listView_41->setPalette(clr_white);}
if (par1.bvv_DI_2 & (1 << 9)){ui->listView_42->setPalette(clr_banana);}
else{ui->listView_42->setPalette(clr_white);}
if (par1.bvv_DI_2 & (1 << 10)){ui->listView_43->setPalette(clr_banana);}
else{ui->listView_43->setPalette(clr_white);}
if (par1.bvv_DI_2 & (1 << 11)){ui->listView_44->setPalette(clr_banana);}
else{ui->listView_44->setPalette(clr_white);}
if (par1.bvv_DI_2 & (1 << 12)){ui->listView_45->setPalette(clr_banana);}
else{ui->listView_45->setPalette(clr_white);}
if (par1.bvv_DI_2 & (1 << 13)){ui->listView_46->setPalette(clr_banana);}
else{ui->listView_46->setPalette(clr_white);}
if (par1.bvv_DI_2 & (1 << 14)){ui->listView_47->setPalette(clr_banana);}
else{ui->listView_47->setPalette(clr_white);}
if (par1.bvv_DI_2 & (1 << 15)){ui->listView_48->setPalette(clr_banana);}
else{ui->listView_48->setPalette(clr_white);}

//-------------------BVV3---------------------------
if (par1.bvv_DI_3 & (1 << 0)){ui->listView_65->setPalette(clr_banana);}
else{ui->listView_65->setPalette(clr_white);}
if (par1.bvv_DI_3 & (1 << 1)){ui->listView_66->setPalette(clr_banana);}
else{ui->listView_66->setPalette(clr_white);}
if (par1.bvv_DI_3 & (1 << 2)){ui->listView_67->setPalette(clr_banana);}
else{ui->listView_67->setPalette(clr_white);}
if (par1.bvv_DI_3 & (1 << 3)){ui->listView_68->setPalette(clr_banana);}
else{ui->listView_68->setPalette(clr_white);}
if (par1.bvv_DI_3 & (1 << 4)){ui->listView_69->setPalette(clr_banana);}
else{ui->listView_69->setPalette(clr_white);}
if (par1.bvv_DI_3 & (1 << 5)){ui->listView_70->setPalette(clr_banana);}
else{ui->listView_70->setPalette(clr_white);}
if (par1.bvv_DI_3 & (1 << 6)){ui->listView_71->setPalette(clr_banana);}
else{ui->listView_71->setPalette(clr_white);}
if (par1.bvv_DI_3 & (1 << 7)){ui->listView_72->setPalette(clr_banana);}
else{ui->listView_72->setPalette(clr_white);}
if (par1.bvv_DI_3 & (1 << 8)){ui->listView_73->setPalette(clr_banana);}
else{ui->listView_73->setPalette(clr_white);}
if (par1.bvv_DI_3 & (1 << 9)){ui->listView_74->setPalette(clr_banana);}
else{ui->listView_74->setPalette(clr_white);}
if (par1.bvv_DI_3 & (1 << 10)){ui->listView_75->setPalette(clr_banana);}
else{ui->listView_75->setPalette(clr_white);}
if (par1.bvv_DI_3 & (1 << 11)){ui->listView_76->setPalette(clr_banana);}
else{ui->listView_76->setPalette(clr_white);}
if (par1.bvv_DI_3 & (1 << 12)){ui->listView_77->setPalette(clr_banana);}
else{ui->listView_77->setPalette(clr_white);}
if (par1.bvv_DI_3 & (1 << 13)){ui->listView_78->setPalette(clr_banana);}
else{ui->listView_78->setPalette(clr_white);}
if (par1.bvv_DI_3 & (1 << 14)){ui->listView_79->setPalette(clr_banana);}
else{ui->listView_79->setPalette(clr_white);}
if (par1.bvv_DI_3 & (1 << 15)){ui->listView_80->setPalette(clr_banana);}
else{ui->listView_80->setPalette(clr_white);}

//-------------------BVV4---------------------------
if (par1.bvv_DI_4 & (1 << 0)){ui->listView_97->setPalette(clr_banana);}
else{ui->listView_97->setPalette(clr_white);}
if (par1.bvv_DI_4 & (1 << 1)){ui->listView_98->setPalette(clr_banana);}
else{ui->listView_98->setPalette(clr_white);}
if (par1.bvv_DI_4 & (1 << 2)){ui->listView_99->setPalette(clr_banana);}
else{ui->listView_99->setPalette(clr_white);}
if (par1.bvv_DI_4 & (1 << 3)){ui->listView_100->setPalette(clr_banana);}
else{ui->listView_100->setPalette(clr_white);}
if (par1.bvv_DI_4 & (1 << 4)){ui->listView_101->setPalette(clr_banana);}
else{ui->listView_101->setPalette(clr_white);}
if (par1.bvv_DI_4 & (1 << 5)){ui->listView_102->setPalette(clr_banana);}
else{ui->listView_102->setPalette(clr_white);}
if (par1.bvv_DI_4 & (1 << 6)){ui->listView_103->setPalette(clr_banana);}
else{ui->listView_103->setPalette(clr_white);}
if (par1.bvv_DI_4 & (1 << 7)){ui->listView_104->setPalette(clr_banana);}
else{ui->listView_104->setPalette(clr_white);}
if (par1.bvv_DI_4 & (1 << 8)){ui->listView_105->setPalette(clr_banana);}
else{ui->listView_105->setPalette(clr_white);}
if (par1.bvv_DI_4 & (1 << 9)){ui->listView_106->setPalette(clr_banana);}
else{ui->listView_106->setPalette(clr_white);}
if (par1.bvv_DI_4 & (1 << 10)){ui->listView_107->setPalette(clr_banana);}
else{ui->listView_107->setPalette(clr_white);}
if (par1.bvv_DI_4 & (1 << 11)){ui->listView_108->setPalette(clr_banana);}
else{ui->listView_108->setPalette(clr_white);}
if (par1.bvv_DI_4 & (1 << 12)){ui->listView_109->setPalette(clr_banana);}
else{ui->listView_109->setPalette(clr_white);}
if (par1.bvv_DI_4 & (1 << 13)){ui->listView_110->setPalette(clr_banana);}
else{ui->listView_110->setPalette(clr_white);}
if (par1.bvv_DI_4 & (1 << 14)){ui->listView_111->setPalette(clr_banana);}
else{ui->listView_111->setPalette(clr_white);}
if (par1.bvv_DI_4 & (1 << 15)){ui->listView_112->setPalette(clr_banana);}
else{ui->listView_112->setPalette(clr_white);}

//-------------------BVV5---------------------------
if (par1.bvv_DI_5 & (1 << 0)){ui->listView_129->setPalette(clr_banana);}
else{ui->listView_129->setPalette(clr_white);}
if (par1.bvv_DI_5 & (1 << 1)){ui->listView_130->setPalette(clr_banana);}
else{ui->listView_130->setPalette(clr_white);}
if (par1.bvv_DI_5 & (1 << 2)){ui->listView_131->setPalette(clr_banana);}
else{ui->listView_131->setPalette(clr_white);}
if (par1.bvv_DI_5 & (1 << 3)){ui->listView_132->setPalette(clr_banana);}
else{ui->listView_132->setPalette(clr_white);}
if (par1.bvv_DI_5 & (1 << 4)){ui->listView_133->setPalette(clr_banana);}
else{ui->listView_133->setPalette(clr_white);}
if (par1.bvv_DI_5 & (1 << 5)){ui->listView_134->setPalette(clr_banana);}
else{ui->listView_134->setPalette(clr_white);}
if (par1.bvv_DI_5 & (1 << 6)){ui->listView_135->setPalette(clr_banana);}
else{ui->listView_135->setPalette(clr_white);}
if (par1.bvv_DI_5 & (1 << 7)){ui->listView_136->setPalette(clr_banana);}
else{ui->listView_136->setPalette(clr_white);}
if (par1.bvv_DI_5 & (1 << 8)){ui->listView_137->setPalette(clr_banana);}
else{ui->listView_137->setPalette(clr_white);}
if (par1.bvv_DI_5 & (1 << 9)){ui->listView_138->setPalette(clr_banana);}
else{ui->listView_138->setPalette(clr_white);}
if (par1.bvv_DI_5 & (1 << 10)){ui->listView_139->setPalette(clr_banana);}
else{ui->listView_139->setPalette(clr_white);}
if (par1.bvv_DI_5 & (1 << 11)){ui->listView_140->setPalette(clr_banana);}
else{ui->listView_140->setPalette(clr_white);}
if (par1.bvv_DI_5 & (1 << 12)){ui->listView_141->setPalette(clr_banana);}
else{ui->listView_141->setPalette(clr_white);}
if (par1.bvv_DI_5 & (1 << 13)){ui->listView_142->setPalette(clr_banana);}
else{ui->listView_142->setPalette(clr_white);}
if (par1.bvv_DI_5 & (1 << 14)){ui->listView_143->setPalette(clr_banana);}
else{ui->listView_143->setPalette(clr_white);}
if (par1.bvv_DI_5 & (1 << 15)){ui->listView_144->setPalette(clr_banana);}
else{ui->listView_144->setPalette(clr_white);}

//-------------------BVV6---------------------------
if (par1.bvv_DI_6 & (1 << 0)){ui->listView_161->setPalette(clr_banana);}
else{ui->listView_161->setPalette(clr_white);}
if (par1.bvv_DI_6 & (1 << 1)){ui->listView_162->setPalette(clr_banana);}
else{ui->listView_162->setPalette(clr_white);}
if (par1.bvv_DI_6 & (1 << 2)){ui->listView_163->setPalette(clr_banana);}
else{ui->listView_163->setPalette(clr_white);}
if (par1.bvv_DI_6 & (1 << 3)){ui->listView_164->setPalette(clr_banana);}
else{ui->listView_164->setPalette(clr_white);}
if (par1.bvv_DI_6 & (1 << 4)){ui->listView_165->setPalette(clr_banana);}
else{ui->listView_165->setPalette(clr_white);}
if (par1.bvv_DI_6 & (1 << 5)){ui->listView_166->setPalette(clr_banana);}
else{ui->listView_166->setPalette(clr_white);}
if (par1.bvv_DI_6 & (1 << 6)){ui->listView_167->setPalette(clr_banana);}
else{ui->listView_167->setPalette(clr_white);}
if (par1.bvv_DI_6 & (1 << 7)){ui->listView_168->setPalette(clr_banana);}
else{ui->listView_168->setPalette(clr_white);}
if (par1.bvv_DI_6 & (1 << 8)){ui->listView_169->setPalette(clr_banana);}
else{ui->listView_169->setPalette(clr_white);}
if (par1.bvv_DI_6 & (1 << 9)){ui->listView_170->setPalette(clr_banana);}
else{ui->listView_170->setPalette(clr_white);}
if (par1.bvv_DI_6 & (1 << 10)){ui->listView_171->setPalette(clr_banana);}
else{ui->listView_171->setPalette(clr_white);}
if (par1.bvv_DI_6 & (1 << 11)){ui->listView_172->setPalette(clr_banana);}
else{ui->listView_172->setPalette(clr_white);}
if (par1.bvv_DI_6 & (1 << 12)){ui->listView_173->setPalette(clr_banana);}
else{ui->listView_173->setPalette(clr_white);}
if (par1.bvv_DI_6 & (1 << 13)){ui->listView_174->setPalette(clr_banana);}
else{ui->listView_174->setPalette(clr_white);}
if (par1.bvv_DI_6 & (1 << 14)){ui->listView_175->setPalette(clr_banana);}
else{ui->listView_175->setPalette(clr_white);}
if (par1.bvv_DI_6 & (1 << 15)){ui->listView_176->setPalette(clr_banana);}
else{ui->listView_176->setPalette(clr_white);}

//-------------------BVV7---------------------------
if (par1.bvv_DI_7 & (1 << 0)){ui->listView_193->setPalette(clr_banana);}
else{ui->listView_193->setPalette(clr_white);}
if (par1.bvv_DI_7 & (1 << 1)){ui->listView_194->setPalette(clr_banana);}
else{ui->listView_194->setPalette(clr_white);}
if (par1.bvv_DI_7 & (1 << 2)){ui->listView_195->setPalette(clr_banana);}
else{ui->listView_195->setPalette(clr_white);}
if (par1.bvv_DI_7 & (1 << 3)){ui->listView_196->setPalette(clr_banana);}
else{ui->listView_196->setPalette(clr_white);}
if (par1.bvv_DI_7 & (1 << 4)){ui->listView_197->setPalette(clr_banana);}
else{ui->listView_197->setPalette(clr_white);}
if (par1.bvv_DI_7 & (1 << 5)){ui->listView_198->setPalette(clr_banana);}
else{ui->listView_198->setPalette(clr_white);}
if (par1.bvv_DI_7 & (1 << 6)){ui->listView_199->setPalette(clr_banana);}
else{ui->listView_199->setPalette(clr_white);}
if (par1.bvv_DI_7 & (1 << 7)){ui->listView_200->setPalette(clr_banana);}
else{ui->listView_200->setPalette(clr_white);}
if (par1.bvv_DI_7 & (1 << 8)){ui->listView_201->setPalette(clr_banana);}
else{ui->listView_201->setPalette(clr_white);}
if (par1.bvv_DI_7 & (1 << 9)){ui->listView_202->setPalette(clr_banana);}
else{ui->listView_202->setPalette(clr_white);}
if (par1.bvv_DI_7 & (1 << 10)){ui->listView_203->setPalette(clr_banana);}
else{ui->listView_203->setPalette(clr_white);}
if (par1.bvv_DI_7 & (1 << 11)){ui->listView_204->setPalette(clr_banana);}
else{ui->listView_204->setPalette(clr_white);}
if (par1.bvv_DI_7 & (1 << 12)){ui->listView_205->setPalette(clr_banana);}
else{ui->listView_205->setPalette(clr_white);}
if (par1.bvv_DI_7 & (1 << 13)){ui->listView_206->setPalette(clr_banana);}
else{ui->listView_206->setPalette(clr_white);}
if (par1.bvv_DI_7 & (1 << 14)){ui->listView_207->setPalette(clr_banana);}
else{ui->listView_207->setPalette(clr_white);}
if (par1.bvv_DI_7 & (1 << 15)){ui->listView_208->setPalette(clr_banana);}
else{ui->listView_208->setPalette(clr_white);}

//-------------------BVV8---------------------------
if (par1.bvv_DI_8 & (1 << 0)){ui->listView_225->setPalette(clr_banana);}
else{ui->listView_225->setPalette(clr_white);}
if (par1.bvv_DI_8 & (1 << 1)){ui->listView_226->setPalette(clr_banana);}
else{ui->listView_226->setPalette(clr_white);}
if (par1.bvv_DI_8 & (1 << 2)){ui->listView_227->setPalette(clr_banana);}
else{ui->listView_227->setPalette(clr_white);}
if (par1.bvv_DI_8 & (1 << 3)){ui->listView_228->setPalette(clr_banana);}
else{ui->listView_228->setPalette(clr_white);}
if (par1.bvv_DI_8 & (1 << 4)){ui->listView_229->setPalette(clr_banana);}
else{ui->listView_229->setPalette(clr_white);}
if (par1.bvv_DI_8 & (1 << 5)){ui->listView_230->setPalette(clr_banana);}
else{ui->listView_230->setPalette(clr_white);}
if (par1.bvv_DI_8 & (1 << 6)){ui->listView_231->setPalette(clr_banana);}
else{ui->listView_231->setPalette(clr_white);}
if (par1.bvv_DI_8 & (1 << 7)){ui->listView_232->setPalette(clr_banana);}
else{ui->listView_232->setPalette(clr_white);}
if (par1.bvv_DI_8 & (1 << 8)){ui->listView_233->setPalette(clr_banana);}
else{ui->listView_233->setPalette(clr_white);}
if (par1.bvv_DI_8 & (1 << 9)){ui->listView_234->setPalette(clr_banana);}
else{ui->listView_234->setPalette(clr_white);}
if (par1.bvv_DI_8 & (1 << 10)){ui->listView_235->setPalette(clr_banana);}
else{ui->listView_235->setPalette(clr_white);}
if (par1.bvv_DI_8 & (1 << 11)){ui->listView_236->setPalette(clr_banana);}
else{ui->listView_236->setPalette(clr_white);}
if (par1.bvv_DI_8 & (1 << 12)){ui->listView_237->setPalette(clr_banana);}
else{ui->listView_237->setPalette(clr_white);}
if (par1.bvv_DI_8 & (1 << 13)){ui->listView_238->setPalette(clr_banana);}
else{ui->listView_238->setPalette(clr_white);}
if (par1.bvv_DI_8 & (1 << 14)){ui->listView_239->setPalette(clr_banana);}
else{ui->listView_239->setPalette(clr_white);}
if (par1.bvv_DI_8 & (1 << 15)){ui->listView_240->setPalette(clr_banana);}
else{ui->listView_240->setPalette(clr_white);}

//-------------------BVV9---------------------------
if (par1.bvv_DI_9 & (1 << 0)){ui->listView_257->setPalette(clr_banana);}
else{ui->listView_257->setPalette(clr_white);}
if (par1.bvv_DI_9 & (1 << 1)){ui->listView_258->setPalette(clr_banana);}
else{ui->listView_258->setPalette(clr_white);}
if (par1.bvv_DI_9 & (1 << 2)){ui->listView_259->setPalette(clr_banana);}
else{ui->listView_259->setPalette(clr_white);}
if (par1.bvv_DI_9 & (1 << 3)){ui->listView_260->setPalette(clr_banana);}
else{ui->listView_260->setPalette(clr_white);}
if (par1.bvv_DI_9 & (1 << 4)){ui->listView_261->setPalette(clr_banana);}
else{ui->listView_261->setPalette(clr_white);}
if (par1.bvv_DI_9 & (1 << 5)){ui->listView_262->setPalette(clr_banana);}
else{ui->listView_262->setPalette(clr_white);}
if (par1.bvv_DI_9 & (1 << 6)){ui->listView_263->setPalette(clr_banana);}
else{ui->listView_263->setPalette(clr_white);}
if (par1.bvv_DI_9 & (1 << 7)){ui->listView_264->setPalette(clr_banana);}
else{ui->listView_264->setPalette(clr_white);}
if (par1.bvv_DI_9 & (1 << 8)){ui->listView_265->setPalette(clr_banana);}
else{ui->listView_265->setPalette(clr_white);}
if (par1.bvv_DI_9 & (1 << 9)){ui->listView_266->setPalette(clr_banana);}
else{ui->listView_266->setPalette(clr_white);}
if (par1.bvv_DI_9 & (1 << 10)){ui->listView_267->setPalette(clr_banana);}
else{ui->listView_267->setPalette(clr_white);}
if (par1.bvv_DI_9 & (1 << 11)){ui->listView_268->setPalette(clr_banana);}
else{ui->listView_268->setPalette(clr_white);}
if (par1.bvv_DI_9 & (1 << 12)){ui->listView_269->setPalette(clr_banana);}
else{ui->listView_269->setPalette(clr_white);}
if (par1.bvv_DI_9 & (1 << 13)){ui->listView_270->setPalette(clr_banana);}
else{ui->listView_270->setPalette(clr_white);}
if (par1.bvv_DI_9 & (1 << 14)){ui->listView_271->setPalette(clr_banana);}
else{ui->listView_271->setPalette(clr_white);}
if (par1.bvv_DI_9 & (1 << 15)){ui->listView_272->setPalette(clr_banana);}
else{ui->listView_272->setPalette(clr_white);}
//-----------------------------------------------------
}
void servicewindow::bvv_out(bvv_DO par2)
{
    //-------------------BVV1---------------------------
    if (par2.bvv_DO_1 & (1 << 0)){ui->listView_17->setPalette(clr_banana);}
    else{ui->listView_17->setPalette(clr_white);}
    if (par2.bvv_DO_1 & (1 << 1)){ui->listView_18->setPalette(clr_banana);}
    else{ui->listView_18->setPalette(clr_white);}
    if (par2.bvv_DO_1 & (1 << 2)){ui->listView_19->setPalette(clr_banana);}
    else{ui->listView_19->setPalette(clr_white);}
    if (par2.bvv_DO_1 & (1 << 3)){ui->listView_20->setPalette(clr_banana);}
    else{ui->listView_20->setPalette(clr_white);}
    if (par2.bvv_DO_1 & (1 << 4)){ui->listView_21->setPalette(clr_banana);}
    else{ui->listView_21->setPalette(clr_white);}
    if (par2.bvv_DO_1 & (1 << 5)){ui->listView_22->setPalette(clr_banana);}
    else{ui->listView_22->setPalette(clr_white);}
    if (par2.bvv_DO_1 & (1 << 6)){ui->listView_23->setPalette(clr_banana);}
    else{ui->listView_23->setPalette(clr_white);}
    if (par2.bvv_DO_1 & (1 << 7)){ui->listView_24->setPalette(clr_banana);}
    else{ui->listView_24->setPalette(clr_white);}
    if (par2.bvv_DO_1 & (1 << 8)){ui->listView_25->setPalette(clr_banana);}
    else{ui->listView_25->setPalette(clr_white);}
    if (par2.bvv_DO_1 & (1 << 9)){ui->listView_26->setPalette(clr_banana);}
    else{ui->listView_26->setPalette(clr_white);}
    if (par2.bvv_DO_1 & (1 << 10)){ui->listView_27->setPalette(clr_banana);}
    else{ui->listView_27->setPalette(clr_white);}
    if (par2.bvv_DO_1 & (1 << 11)){ui->listView_28->setPalette(clr_banana);}
    else{ui->listView_28->setPalette(clr_white);}
    if (par2.bvv_DO_1 & (1 << 12)){ui->listView_29->setPalette(clr_banana);}
    else{ui->listView_29->setPalette(clr_white);}
    if (par2.bvv_DO_1 & (1 << 13)){ui->listView_30->setPalette(clr_banana);}
    else{ui->listView_30->setPalette(clr_white);}
    if (par2.bvv_DO_1 & (1 << 14)){ui->listView_31->setPalette(clr_banana);}
    else{ui->listView_31->setPalette(clr_white);}
    if (par2.bvv_DO_1 & (1 << 15)){ui->listView_32->setPalette(clr_banana);}
    else{ui->listView_32->setPalette(clr_white);}

    //-------------------BVV2---------------------------
    if (par2.bvv_DO_2 & (1 << 0)){ui->listView_49->setPalette(clr_banana);}
    else{ui->listView_49->setPalette(clr_white);}
    if (par2.bvv_DO_2 & (1 << 1)){ui->listView_50->setPalette(clr_banana);}
    else{ui->listView_50->setPalette(clr_white);}
    if (par2.bvv_DO_2 & (1 << 2)){ui->listView_51->setPalette(clr_banana);}
    else{ui->listView_51->setPalette(clr_white);}
    if (par2.bvv_DO_2 & (1 << 3)){ui->listView_52->setPalette(clr_banana);}
    else{ui->listView_52->setPalette(clr_white);}
    if (par2.bvv_DO_2 & (1 << 4)){ui->listView_53->setPalette(clr_banana);}
    else{ui->listView_53->setPalette(clr_white);}
    if (par2.bvv_DO_2 & (1 << 5)){ui->listView_54->setPalette(clr_banana);}
    else{ui->listView_54->setPalette(clr_white);}
    if (par2.bvv_DO_2 & (1 << 6)){ui->listView_55->setPalette(clr_banana);}
    else{ui->listView_55->setPalette(clr_white);}
    if (par2.bvv_DO_2 & (1 << 7)){ui->listView_56->setPalette(clr_banana);}
    else{ui->listView_56->setPalette(clr_white);}
    if (par2.bvv_DO_2 & (1 << 8)){ui->listView_57->setPalette(clr_banana);}
    else{ui->listView_57->setPalette(clr_white);}
    if (par2.bvv_DO_2 & (1 << 9)){ui->listView_58->setPalette(clr_banana);}
    else{ui->listView_58->setPalette(clr_white);}
    if (par2.bvv_DO_2 & (1 << 10)){ui->listView_59->setPalette(clr_banana);}
    else{ui->listView_59->setPalette(clr_white);}
    if (par2.bvv_DO_2 & (1 << 11)){ui->listView_60->setPalette(clr_banana);}
    else{ui->listView_60->setPalette(clr_white);}
    if (par2.bvv_DO_2 & (1 << 12)){ui->listView_61->setPalette(clr_banana);}
    else{ui->listView_61->setPalette(clr_white);}
    if (par2.bvv_DO_2 & (1 << 13)){ui->listView_62->setPalette(clr_banana);}
    else{ui->listView_62->setPalette(clr_white);}
    if (par2.bvv_DO_2 & (1 << 14)){ui->listView_63->setPalette(clr_banana);}
    else{ui->listView_63->setPalette(clr_white);}
    if (par2.bvv_DO_2 & (1 << 15)){ui->listView_64->setPalette(clr_banana);}
    else{ui->listView_64->setPalette(clr_white);}

    //-------------------BVV3---------------------------
    if (par2.bvv_DO_3 & (1 << 0)){ui->listView_81->setPalette(clr_banana);}
    else{ui->listView_81->setPalette(clr_white);}
    if (par2.bvv_DO_3 & (1 << 1)){ui->listView_82->setPalette(clr_banana);}
    else{ui->listView_82->setPalette(clr_white);}
    if (par2.bvv_DO_3 & (1 << 2)){ui->listView_83->setPalette(clr_banana);}
    else{ui->listView_83->setPalette(clr_white);}
    if (par2.bvv_DO_3 & (1 << 3)){ui->listView_84->setPalette(clr_banana);}
    else{ui->listView_84->setPalette(clr_white);}
    if (par2.bvv_DO_3 & (1 << 4)){ui->listView_85->setPalette(clr_banana);}
    else{ui->listView_85->setPalette(clr_white);}
    if (par2.bvv_DO_3 & (1 << 5)){ui->listView_86->setPalette(clr_banana);}
    else{ui->listView_86->setPalette(clr_white);}
    if (par2.bvv_DO_3 & (1 << 6)){ui->listView_87->setPalette(clr_banana);}
    else{ui->listView_87->setPalette(clr_white);}
    if (par2.bvv_DO_3 & (1 << 7)){ui->listView_88->setPalette(clr_banana);}
    else{ui->listView_88->setPalette(clr_white);}
    if (par2.bvv_DO_3 & (1 << 8)){ui->listView_89->setPalette(clr_banana);}
    else{ui->listView_89->setPalette(clr_white);}
    if (par2.bvv_DO_3 & (1 << 9)){ui->listView_90->setPalette(clr_banana);}
    else{ui->listView_90->setPalette(clr_white);}
    if (par2.bvv_DO_3 & (1 << 10)){ui->listView_91->setPalette(clr_banana);}
    else{ui->listView_91->setPalette(clr_white);}
    if (par2.bvv_DO_3 & (1 << 11)){ui->listView_92->setPalette(clr_banana);}
    else{ui->listView_92->setPalette(clr_white);}
    if (par2.bvv_DO_3 & (1 << 12)){ui->listView_93->setPalette(clr_banana);}
    else{ui->listView_93->setPalette(clr_white);}
    if (par2.bvv_DO_3 & (1 << 13)){ui->listView_94->setPalette(clr_banana);}
    else{ui->listView_94->setPalette(clr_white);}
    if (par2.bvv_DO_3 & (1 << 14)){ui->listView_95->setPalette(clr_banana);}
    else{ui->listView_95->setPalette(clr_white);}
    if (par2.bvv_DO_3 & (1 << 15)){ui->listView_96->setPalette(clr_banana);}
    else{ui->listView_96->setPalette(clr_white);}

    //-------------------BVV4---------------------------
    if (par2.bvv_DO_4 & (1 << 0)){ui->listView_113->setPalette(clr_banana);}
    else{ui->listView_113->setPalette(clr_white);}
    if (par2.bvv_DO_4 & (1 << 1)){ui->listView_114->setPalette(clr_banana);}
    else{ui->listView_114->setPalette(clr_white);}
    if (par2.bvv_DO_4 & (1 << 2)){ui->listView_115->setPalette(clr_banana);}
    else{ui->listView_115->setPalette(clr_white);}
    if (par2.bvv_DO_4 & (1 << 3)){ui->listView_116->setPalette(clr_banana);}
    else{ui->listView_116->setPalette(clr_white);}
    if (par2.bvv_DO_4 & (1 << 4)){ui->listView_117->setPalette(clr_banana);}
    else{ui->listView_117->setPalette(clr_white);}
    if (par2.bvv_DO_4 & (1 << 5)){ui->listView_118->setPalette(clr_banana);}
    else{ui->listView_118->setPalette(clr_white);}
    if (par2.bvv_DO_4 & (1 << 6)){ui->listView_119->setPalette(clr_banana);}
    else{ui->listView_119->setPalette(clr_white);}
    if (par2.bvv_DO_4 & (1 << 7)){ui->listView_120->setPalette(clr_banana);}
    else{ui->listView_120->setPalette(clr_white);}
    if (par2.bvv_DO_4 & (1 << 8)){ui->listView_121->setPalette(clr_banana);}
    else{ui->listView_121->setPalette(clr_white);}
    if (par2.bvv_DO_4 & (1 << 9)){ui->listView_122->setPalette(clr_banana);}
    else{ui->listView_122->setPalette(clr_white);}
    if (par2.bvv_DO_4 & (1 << 10)){ui->listView_123->setPalette(clr_banana);}
    else{ui->listView_123->setPalette(clr_white);}
    if (par2.bvv_DO_4 & (1 << 11)){ui->listView_124->setPalette(clr_banana);}
    else{ui->listView_124->setPalette(clr_white);}
    if (par2.bvv_DO_4 & (1 << 12)){ui->listView_125->setPalette(clr_banana);}
    else{ui->listView_125->setPalette(clr_white);}
    if (par2.bvv_DO_4 & (1 << 13)){ui->listView_126->setPalette(clr_banana);}
    else{ui->listView_126->setPalette(clr_white);}
    if (par2.bvv_DO_4 & (1 << 14)){ui->listView_127->setPalette(clr_banana);}
    else{ui->listView_127->setPalette(clr_white);}
    if (par2.bvv_DO_4 & (1 << 15)){ui->listView_128->setPalette(clr_banana);}
    else{ui->listView_128->setPalette(clr_white);}

    //-------------------BVV5---------------------------
    if (par2.bvv_DO_5 & (1 << 0)){ui->listView_145->setPalette(clr_banana);}
    else{ui->listView_145->setPalette(clr_white);}
    if (par2.bvv_DO_5 & (1 << 1)){ui->listView_146->setPalette(clr_banana);}
    else{ui->listView_146->setPalette(clr_white);}
    if (par2.bvv_DO_5 & (1 << 2)){ui->listView_147->setPalette(clr_banana);}
    else{ui->listView_147->setPalette(clr_white);}
    if (par2.bvv_DO_5 & (1 << 3)){ui->listView_148->setPalette(clr_banana);}
    else{ui->listView_148->setPalette(clr_white);}
    if (par2.bvv_DO_5 & (1 << 4)){ui->listView_149->setPalette(clr_banana);}
    else{ui->listView_149->setPalette(clr_white);}
    if (par2.bvv_DO_5 & (1 << 5)){ui->listView_150->setPalette(clr_banana);}
    else{ui->listView_150->setPalette(clr_white);}
    if (par2.bvv_DO_5 & (1 << 6)){ui->listView_151->setPalette(clr_banana);}
    else{ui->listView_151->setPalette(clr_white);}
    if (par2.bvv_DO_5 & (1 << 7)){ui->listView_152->setPalette(clr_banana);}
    else{ui->listView_152->setPalette(clr_white);}
    if (par2.bvv_DO_5 & (1 << 8)){ui->listView_153->setPalette(clr_banana);}
    else{ui->listView_153->setPalette(clr_white);}
    if (par2.bvv_DO_5 & (1 << 9)){ui->listView_154->setPalette(clr_banana);}
    else{ui->listView_154->setPalette(clr_white);}
    if (par2.bvv_DO_5 & (1 << 10)){ui->listView_155->setPalette(clr_banana);}
    else{ui->listView_155->setPalette(clr_white);}
    if (par2.bvv_DO_5 & (1 << 11)){ui->listView_156->setPalette(clr_banana);}
    else{ui->listView_156->setPalette(clr_white);}
    if (par2.bvv_DO_5 & (1 << 12)){ui->listView_157->setPalette(clr_banana);}
    else{ui->listView_157->setPalette(clr_white);}
    if (par2.bvv_DO_5 & (1 << 13)){ui->listView_158->setPalette(clr_banana);}
    else{ui->listView_158->setPalette(clr_white);}
    if (par2.bvv_DO_5 & (1 << 14)){ui->listView_159->setPalette(clr_banana);}
    else{ui->listView_159->setPalette(clr_white);}
    if (par2.bvv_DO_5 & (1 << 15)){ui->listView_160->setPalette(clr_banana);}
    else{ui->listView_160->setPalette(clr_white);}

    //-------------------BVV6---------------------------
    if (par2.bvv_DO_6 & (1 << 0)){ui->listView_177->setPalette(clr_banana);}
    else{ui->listView_177->setPalette(clr_white);}
    if (par2.bvv_DO_6 & (1 << 1)){ui->listView_178->setPalette(clr_banana);}
    else{ui->listView_178->setPalette(clr_white);}
    if (par2.bvv_DO_6 & (1 << 2)){ui->listView_179->setPalette(clr_banana);}
    else{ui->listView_179->setPalette(clr_white);}
    if (par2.bvv_DO_6 & (1 << 3)){ui->listView_180->setPalette(clr_banana);}
    else{ui->listView_180->setPalette(clr_white);}
    if (par2.bvv_DO_6 & (1 << 4)){ui->listView_181->setPalette(clr_banana);}
    else{ui->listView_181->setPalette(clr_white);}
    if (par2.bvv_DO_6 & (1 << 5)){ui->listView_182->setPalette(clr_banana);}
    else{ui->listView_182->setPalette(clr_white);}
    if (par2.bvv_DO_6 & (1 << 6)){ui->listView_183->setPalette(clr_banana);}
    else{ui->listView_183->setPalette(clr_white);}
    if (par2.bvv_DO_6 & (1 << 7)){ui->listView_184->setPalette(clr_banana);}
    else{ui->listView_184->setPalette(clr_white);}
    if (par2.bvv_DO_6 & (1 << 8)){ui->listView_185->setPalette(clr_banana);}
    else{ui->listView_185->setPalette(clr_white);}
    if (par2.bvv_DO_6 & (1 << 9)){ui->listView_186->setPalette(clr_banana);}
    else{ui->listView_186->setPalette(clr_white);}
    if (par2.bvv_DO_6 & (1 << 10)){ui->listView_187->setPalette(clr_banana);}
    else{ui->listView_187->setPalette(clr_white);}
    if (par2.bvv_DO_6 & (1 << 11)){ui->listView_188->setPalette(clr_banana);}
    else{ui->listView_188->setPalette(clr_white);}
    if (par2.bvv_DO_6 & (1 << 12)){ui->listView_189->setPalette(clr_banana);}
    else{ui->listView_189->setPalette(clr_white);}
    if (par2.bvv_DO_6 & (1 << 13)){ui->listView_190->setPalette(clr_banana);}
    else{ui->listView_190->setPalette(clr_white);}
    if (par2.bvv_DO_6 & (1 << 14)){ui->listView_191->setPalette(clr_banana);}
    else{ui->listView_191->setPalette(clr_white);}
    if (par2.bvv_DO_6 & (1 << 15)){ui->listView_192->setPalette(clr_banana);}
    else{ui->listView_192->setPalette(clr_white);}

    //-------------------BVV7---------------------------
    if (par2.bvv_DO_7 & (1 << 0)){ui->listView_209->setPalette(clr_banana);}
    else{ui->listView_209->setPalette(clr_white);}
    if (par2.bvv_DO_7 & (1 << 1)){ui->listView_210->setPalette(clr_banana);}
    else{ui->listView_210->setPalette(clr_white);}
    if (par2.bvv_DO_7 & (1 << 2)){ui->listView_211->setPalette(clr_banana);}
    else{ui->listView_211->setPalette(clr_white);}
    if (par2.bvv_DO_7 & (1 << 3)){ui->listView_212->setPalette(clr_banana);}
    else{ui->listView_212->setPalette(clr_white);}
    if (par2.bvv_DO_7 & (1 << 4)){ui->listView_213->setPalette(clr_banana);}
    else{ui->listView_213->setPalette(clr_white);}
    if (par2.bvv_DO_7 & (1 << 5)){ui->listView_214->setPalette(clr_banana);}
    else{ui->listView_214->setPalette(clr_white);}
    if (par2.bvv_DO_7 & (1 << 6)){ui->listView_215->setPalette(clr_banana);}
    else{ui->listView_215->setPalette(clr_white);}
    if (par2.bvv_DO_7 & (1 << 7)){ui->listView_216->setPalette(clr_banana);}
    else{ui->listView_216->setPalette(clr_white);}
    if (par2.bvv_DO_7 & (1 << 8)){ui->listView_217->setPalette(clr_banana);}
    else{ui->listView_217->setPalette(clr_white);}
    if (par2.bvv_DO_7 & (1 << 9)){ui->listView_218->setPalette(clr_banana);}
    else{ui->listView_218->setPalette(clr_white);}
    if (par2.bvv_DO_7 & (1 << 10)){ui->listView_219->setPalette(clr_banana);}
    else{ui->listView_219->setPalette(clr_white);}
    if (par2.bvv_DO_7 & (1 << 11)){ui->listView_220->setPalette(clr_banana);}
    else{ui->listView_220->setPalette(clr_white);}
    if (par2.bvv_DO_7 & (1 << 12)){ui->listView_221->setPalette(clr_banana);}
    else{ui->listView_221->setPalette(clr_white);}
    if (par2.bvv_DO_7 & (1 << 13)){ui->listView_222->setPalette(clr_banana);}
    else{ui->listView_222->setPalette(clr_white);}
    if (par2.bvv_DO_7 & (1 << 14)){ui->listView_223->setPalette(clr_banana);}
    else{ui->listView_223->setPalette(clr_white);}
    if (par2.bvv_DO_7 & (1 << 15)){ui->listView_224->setPalette(clr_banana);}
    else{ui->listView_224->setPalette(clr_white);}

    //-------------------BVV8---------------------------
    if (par2.bvv_DO_8 & (1 << 0)){ui->listView_241->setPalette(clr_banana);}
    else{ui->listView_241->setPalette(clr_white);}
    if (par2.bvv_DO_8 & (1 << 1)){ui->listView_242->setPalette(clr_banana);}
    else{ui->listView_242->setPalette(clr_white);}
    if (par2.bvv_DO_8 & (1 << 2)){ui->listView_243->setPalette(clr_banana);}
    else{ui->listView_243->setPalette(clr_white);}
    if (par2.bvv_DO_8 & (1 << 3)){ui->listView_244->setPalette(clr_banana);}
    else{ui->listView_244->setPalette(clr_white);}
    if (par2.bvv_DO_8 & (1 << 4)){ui->listView_245->setPalette(clr_banana);}
    else{ui->listView_245->setPalette(clr_white);}
    if (par2.bvv_DO_8 & (1 << 5)){ui->listView_246->setPalette(clr_banana);}
    else{ui->listView_246->setPalette(clr_white);}
    if (par2.bvv_DO_8 & (1 << 6)){ui->listView_247->setPalette(clr_banana);}
    else{ui->listView_247->setPalette(clr_white);}
    if (par2.bvv_DO_8 & (1 << 7)){ui->listView_248->setPalette(clr_banana);}
    else{ui->listView_248->setPalette(clr_white);}
    if (par2.bvv_DO_8 & (1 << 8)){ui->listView_249->setPalette(clr_banana);}
    else{ui->listView_249->setPalette(clr_white);}
    if (par2.bvv_DO_8 & (1 << 9)){ui->listView_250->setPalette(clr_banana);}
    else{ui->listView_250->setPalette(clr_white);}
    if (par2.bvv_DO_8 & (1 << 10)){ui->listView_251->setPalette(clr_banana);}
    else{ui->listView_251->setPalette(clr_white);}
    if (par2.bvv_DO_8 & (1 << 11)){ui->listView_252->setPalette(clr_banana);}
    else{ui->listView_252->setPalette(clr_white);}
    if (par2.bvv_DO_8 & (1 << 12)){ui->listView_253->setPalette(clr_banana);}
    else{ui->listView_253->setPalette(clr_white);}
    if (par2.bvv_DO_8 & (1 << 13)){ui->listView_254->setPalette(clr_banana);}
    else{ui->listView_254->setPalette(clr_white);}
    if (par2.bvv_DO_8 & (1 << 14)){ui->listView_255->setPalette(clr_banana);}
    else{ui->listView_255->setPalette(clr_white);}
    if (par2.bvv_DO_8 & (1 << 15)){ui->listView_256->setPalette(clr_banana);}
    else{ui->listView_256->setPalette(clr_white);}

    //-------------------BVV9---------------------------
    if (par2.bvv_DO_9 & (1 << 0)){ui->listView_273->setPalette(clr_banana);}
    else{ui->listView_273->setPalette(clr_white);}
    if (par2.bvv_DO_9 & (1 << 1)){ui->listView_274->setPalette(clr_banana);}
    else{ui->listView_274->setPalette(clr_white);}
    if (par2.bvv_DO_9 & (1 << 2)){ui->listView_275->setPalette(clr_banana);}
    else{ui->listView_275->setPalette(clr_white);}
    if (par2.bvv_DO_9 & (1 << 3)){ui->listView_276->setPalette(clr_banana);}
    else{ui->listView_276->setPalette(clr_white);}
    if (par2.bvv_DO_9 & (1 << 4)){ui->listView_277->setPalette(clr_banana);}
    else{ui->listView_277->setPalette(clr_white);}
    if (par2.bvv_DO_9 & (1 << 5)){ui->listView_278->setPalette(clr_banana);}
    else{ui->listView_278->setPalette(clr_white);}
    if (par2.bvv_DO_9 & (1 << 6)){ui->listView_279->setPalette(clr_banana);}
    else{ui->listView_279->setPalette(clr_white);}
    if (par2.bvv_DO_9 & (1 << 7)){ui->listView_280->setPalette(clr_banana);}
    else{ui->listView_280->setPalette(clr_white);}
    if (par2.bvv_DO_9 & (1 << 8)){ui->listView_281->setPalette(clr_banana);}
    else{ui->listView_281->setPalette(clr_white);}
    if (par2.bvv_DO_9 & (1 << 9)){ui->listView_282->setPalette(clr_banana);}
    else{ui->listView_282->setPalette(clr_white);}
    if (par2.bvv_DO_9 & (1 << 10)){ui->listView_283->setPalette(clr_banana);}
    else{ui->listView_283->setPalette(clr_white);}
    if (par2.bvv_DO_9 & (1 << 11)){ui->listView_284->setPalette(clr_banana);}
    else{ui->listView_284->setPalette(clr_white);}
    if (par2.bvv_DO_9 & (1 << 12)){ui->listView_285->setPalette(clr_banana);}
    else{ui->listView_285->setPalette(clr_white);}
    if (par2.bvv_DO_9 & (1 << 13)){ui->listView_286->setPalette(clr_banana);}
    else{ui->listView_286->setPalette(clr_white);}
    if (par2.bvv_DO_9 & (1 << 14)){ui->listView_287->setPalette(clr_banana);}
    else{ui->listView_287->setPalette(clr_white);}
    if (par2.bvv_DO_9 & (1 << 15)){ui->listView_288->setPalette(clr_banana);}
    else{ui->listView_288->setPalette(clr_white);}
//------------------------------------------------------
}
void servicewindow::device_param(device_parametrs par){
    //---------CONNECTION STATUS-------------------
    ui->label_3->setText(QString::number(par.time_rs485));

           if (par.connection_with_BVV & (1 << 0)){
               ui->listView_bvv_1->setPalette(clr_green);
              } else {ui->listView_bvv_1->setPalette(clr_red); }
           if (par.connection_with_BVV & (1 << 1)){
               ui->listView_bvv_2->setPalette(clr_green);
              } else {ui->listView_bvv_2->setPalette(clr_red); }
           if (par.connection_with_BVV & (1 << 2)){
               ui->listView_bvv_3->setPalette(clr_green);
              } else {ui->listView_bvv_3->setPalette(clr_red); }
           if (par.connection_with_BVV & (1 << 3)){
               ui->listView_bvv_4->setPalette(clr_green);
              } else {ui->listView_bvv_4->setPalette(clr_red); }
           if (par.connection_with_BVV & (1 << 4)){
               ui->listView_bvv_5->setPalette(clr_green);
              } else {ui->listView_bvv_5->setPalette(clr_red); }
           if (par.connection_with_BVV & (1 << 5)){
               ui->listView_bvv_6->setPalette(clr_green);
              } else {ui->listView_bvv_6->setPalette(clr_red); }
           if (par.connection_with_BVV & (1 << 6)){
               ui->listView_bvv_7->setPalette(clr_green);
              } else {ui->listView_bvv_7->setPalette(clr_red); }
           if (par.connection_with_BVV & (1 << 7)){
               ui->listView_bvv_8->setPalette(clr_green);
              } else {ui->listView_bvv_8->setPalette(clr_red); }
           if (par.connection_with_BVV & (1 << 8)){
               ui->listView_bvv_9->setPalette(clr_green);
              } else {ui->listView_bvv_9->setPalette(clr_red); }



}

void servicewindow::on_pushButton_clicked()
{
    this->close();
    emit openmain();
}
void servicewindow::on_pushButton_2_clicked()
{
     QString path("C:\\Users\\ДИГ\\Documents");
     QProcess::startDetached("C:\\Windows\\explorer.exe", {path});
}
void servicewindow::on_pushButton_3_clicked()
{
     QProcess::startDetached("\"C:\\Program Files (x86)\\3S Software\\CoDeSys V2.3\\Codesys.exe""");
}
void servicewindow::on_pushButton_4_clicked()
{
     QProcess::startDetached("\"C:\\Program Files (x86)\\AnyDesk\\AnyDesk.exe""");
}
void servicewindow::on_pushButton_5_clicked()
{
    QString path("C:\\ДИГ\\SCHEMATIC");
    QProcess::startDetached("C:\\Windows\\explorer.exe", {path});
}
void servicewindow::on_pushButton_6_clicked()
{
   QProcess::startDetached("C:/Windows/System32/Taskmgr.exe");
}
void servicewindow::on_pushButton_7_clicked()
{
   QProcess::startDetached("\"C:\\Program Files (x86)\\Microsoft\\Edge\\Application\\msedge.exe""");
}

void servicewindow::on_pushButton_8_clicked()
{
    QProcess::startDetached("\"C:\\Program Files (x86)\\BVV\\io_config.exe""");

}

void servicewindow::on_pushButton_9_clicked()
{
    QProcess::startDetached("\"C:\\Program Files (x86)\\HDplayer\\HDPlayer.exe""");
}

void servicewindow::log()
{
    QDate now = QDate::currentDate();
    ui->calendarWidget->selectedDate() = QDate::currentDate();
    if (ui->calendarWidget->selectedDate() == now){

    QDate yearnow = QDate::currentDate();
    QString yearstamp = yearnow.toString(QLatin1String("yyyy"));

    QString timestamp = now.toString(QLatin1String("dd.MM.yy"));
    QString filename = QString::fromLatin1("C:/DEG/log_PLC_BVV/%1/%2.csv").arg(yearstamp).arg(timestamp);
    QFile file(filename);
 file.close();
    if(file.open(QIODevice::ReadOnly | QIODevice::Text)  )
      {
         QTextStream filename(&file);

         csvModel->clear();

         while (!filename.atEnd())
        {
            csvModel->setHorizontalHeaderLabels(QStringList() << "ВРЕМЯ" << "" << "" << "" << "СООБЩЕНИЕ");
             ui->tableView->setModel(csvModel); // Устанавливаем модель в таблицу
             ui->tableView->setColumnWidth(0,150);
             ui->tableView->setColumnWidth(1,0);
             ui->tableView->setColumnWidth(2,0);
             ui->tableView->setColumnWidth(3,0);
             ui->tableView->setColumnWidth(4,580);
             ui->tableView->setColumnWidth(5,0);
            QString line = filename.readLine();
            // Добавляем в модель по строке с элементами
            QList<QStandardItem *> standardItemsList;

            for (QString item : line.split(";"))
            {
                standardItemsList.append(new QStandardItem(item));
            }
            csvModel->insertRow(csvModel->rowCount(), standardItemsList);
        }
           file.close();
     }

    }
}
void servicewindow::scroll()
{
     QScrollBar *sb = ui->tableView->verticalScrollBar();
     sb->setStyleSheet(QString::fromUtf8("QScrollBar:vertical {"
                                         "    border: 1px solid #999999;"
                                         "    background:white;"
                                         "    width:10px;    "
                                         "    margin: 0px 0px 0px 0px;"
                                         "}"
                                         "QScrollBar::handle:vertical {"
                                         "    background: qlineargradient(x1:0, y1:0, x2:1, y2:0,"
                                         "    stop: 0 rgb(32, 47, 130), stop: 0.5 rgb(32, 47, 130), stop:1 rgb(32, 47, 130));"
                                         "    min-height: 0px;"
                                         "}"
                                         "QScrollBar::add-line:vertical {"
                                         "    background: qlineargradient(x1:0, y1:0, x2:1, y2:0,"
                                         "    stop: 0 rgb(32, 47, 130), stop: 0.5 rgb(32, 47, 130),  stop:1 rgb(32, 47, 130));"
                                         "    height: 0px;"
                                         "    subcontrol-position: bottom;"
                                         "    subcontrol-origin: margin;"
                                         "}"
                                         "QScrollBar::sub-line:vertical {"
                                         "    background: qlineargradient(x1:0, y1:0, x2:1, y2:0,"
                                         "    stop: 0  rgb(32, 47, 130), stop: 0.5 rgb(32, 47, 130),  stop:1 rgb(32, 47, 130));"
                                         "    height: 0 px;"
                                         "    subcontrol-position: top;"
                                         "    subcontrol-origin: margin;"
                                         "}"
                                         ));
     sb->setMaximum(99999);
     sb->setValue(99999);
}
void servicewindow::on_calendarWidget_selectionChanged()
{
    QDate yearnow = ui->calendarWidget->selectedDate();
    QString yearstamp = yearnow.toString(QLatin1String("yyyy"));

       QString timestamp = ui->calendarWidget->selectedDate().toString(QLatin1String("dd.MM.yy"));
       QString filename = QString::fromLatin1("C:/DEG/log_ЗДС_/%1/%2.csv").arg(yearstamp).arg(timestamp);
       QFile file(filename);
        file.close();

       if(file.open(QIODevice::ReadOnly | QIODevice::Text))
         {
            QTextStream filename(&file);
             csvModel->clear();

            while (!filename.atEnd())
           {
                csvModel->setHorizontalHeaderLabels(QStringList() << "ВРЕМЯ" << "" << "" << "" << "СООБЩЕНИЕ");
                ui->tableView->setModel(csvModel); // Устанавливаем модель в таблицу
                ui->tableView->setColumnWidth(0,150);
                ui->tableView->setColumnWidth(1,0);
                ui->tableView->setColumnWidth(2,0);
                ui->tableView->setColumnWidth(3,0);
                ui->tableView->setColumnWidth(4,580);
                ui->tableView->setColumnWidth(5,0);
               QString line = filename.readLine();
               // Добавляем в модель по строке с элементами
               QList<QStandardItem *> standardItemsList;

               for (QString item : line.split(";"))
               {
                   standardItemsList.append(new QStandardItem(item));
               }
               csvModel->insertRow(csvModel->rowCount(), standardItemsList);
           }

              file.close();
        }
}
