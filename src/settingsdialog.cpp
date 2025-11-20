#include "settingsdialog.h"
#include "ui_setting.h"  // 注意：这里应该是你的setting.ui生成的头文件

SettingsDialog::SettingsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingsDialog)  // 确保这里的类名与UI文件中的类名一致
{
    ui->setupUi(this);
    
    // 设置窗口属性
    setWindowTitle("设置");
    setFixedSize(480, 392);  // 与UI文件中的尺寸一致
    
    // 加载当前设置
    loadSettings();
}

SettingsDialog::~SettingsDialog()
{
    delete ui;
}

void SettingsDialog::on_saveButton_clicked()
{
    saveSettings();
    accept();  // 关闭对话框并返回Accepted
}

void SettingsDialog::on_cancelButton_clicked()
{
    reject();  // 关闭对话框并返回Rejected
}

void SettingsDialog::on_applyButton_clicked()
{
    saveSettings();
    // 不关闭对话框，只应用设置
}

void SettingsDialog::saveSettings()
{
    // 这里保存设置到配置文件或内存
    // 例如：QSettings settings;
    // settings.setValue("volume", volumeValue);
    // settings.setValue("theme", themeName);
    
    // 临时：只显示消息
    ui->label->setText("设置已保存!");
}

void SettingsDialog::loadSettings()
{
    // 这里从配置文件或内存加载设置
    // 例如：QSettings settings;
    // int volume = settings.value("volume", 75).toInt();
    // QString theme = settings.value("theme", "default").toString();
    
    // 临时：显示加载消息
    ui->label->setText("设置已加载");
}