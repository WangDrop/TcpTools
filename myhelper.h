#ifndef MYHELPER
#define MYHELPER
#include <QMessageBox>
#include <QDesktopWidget>
#include <QFile>
#include <QAbstractButton>
#include <QCoreApplication>
#include <QFileDialog>
#include <QTime>
#include <QProcess>
#include <QDir>
#include <QSound>
#include <QApplication>
#include <QStyleFactory>
#include <QInputDialog>
#include <QDebug>

//自己平时写的一些Qt的辅助类：
class MyHelper : public QObject{
public:
    //设置全局为Plastique样式
    static void setStyle()
    {
        QApplication::setStyle(QStyleFactory::create("Plastique"));
    }
    //设置编码为GBK2312
    static void setGB2312Codec()
    {
        QTextCodec * codec = QTextCodec::CodecForName("Gb2312");
        QTextCodec::setCodecForLocale(codec);
#ifdef QT4LESS
        QTextCodec::setCodecForCStrings(codec);
        QTextCodec::setCOdecForTr(Tr);
#endif
    }

    static void setUTF8Codec()
    {
        QTextCodec * codec = QTextCodec::CodecForName("UTF-8");
        QTextCodec::setCodecForLocale(codec);
#ifdef QT4LESS
        QTextCodec::setCodecForLocale(codec);
        QTextCodec::setCodecForTr(Tr);
#endif
    }

    //提示信息框，只含有错误按钮
    static void ShowMessageBoxInfo(const QString & info)
    {
        QMessageBox msg;
        msg.setStyleSheet("font:12pt '宋体'");
        msg.setWindowTitle("提示");
        msg.setText(info);
        msg.setIcon(QMessageBox::Information);
        msg.addButton("确定", QMessageBox::ActionRole);
        msg.exec();
    }

    static void ShowMessageBoxInfoX(const QString & info)
    {
        QMessageBox::information(0, "提示", info, QMessageBox::Ok);
    }

    //显示询问按钮，确定以及取消按钮
    static void ShowMessageBoxError(const QString & info)
    {
        QMessageBox msg;
        msg.setStyleSheet("font:12pt '宋体'");
        msg.setWindowTitle("错误");
        msg.setText(info);
        msg.setIcon(QMessageBox::Critical);
        msg.addButton("确定", QMessageBox::ActionRole);
        msg.exec();
    }

    static void ShowMessageBoxErrorX(const QString & info)
    {
        QMessageBox::information(0, "错误", info, QMessageBox::Ok);
    }

    //询问框，确定按钮以及选择按钮
    static int ShowMessageBoxQuestion(const QString & info)
    {
        QMessageBox msg;
        msg.setStyleSheet("font:12px '宋体'");
        msg.setWindowTitle("询问");
        msg.setText(info);
        msg.setIcon(QMessageBox::Question);
        msg.addButton("确定", QMessageBox::ActionRole);
        msg.addButton("取消", QMessageBox::ActionRole);
        return msg.exec();
    }

    static int ShowMessageBoxQuestionX(const QString & info)
    {
        QMessageBox::information(0, "询问", info, QMessageBox::Yes | QMessageBox::No);
    }

    //显示标准的输入框
    static QString ShowInputBox(QWidget * parent, const QString & info)
    {
        bool ok;
        return QInputDialog::getText(parent, "提示", info, QLineEdit::Password, "", &ok);
    }

    //将16进制的字符串转换成字符数组
    static QByteArray HexStrToByteArray(const QString & str)
    {
        QByteArray sendData;
        int hexData, lowHexData;
        int hexDataLen = 0;
        int len = str.length();
        sendData.resize(len/2);
        char lstr, hstr;
        for(int i = 0; i < len;){
            hstr = str[i];
            if(hstr == ' '){
                continue;
            }
            i++;
            if(i > len)
                break;
            lstr = str[i];
            hexData = ConvertHexChar(hstr);
            lowHexData = ConvertHexChar(lstr);
            if(hexData == 16 || lowHexData == 16)
                break;
            else
                hexData = hexData*16 + lowHexData;
            i++;
            sendData[hexDataLen++] = (char)hexData;
        }
        sendData.resize(hexDataLen);
        return sendData;
    }

    static char ConvertHexChar(char ch)
    {
        if(ch >= '0' && ch <= '9')
            return ch - 0x30;
        else if(ch >= 'A' && ch <= 'F')
            return ch - 'A' + 10;
        else if(ch >= 'a' && ch <= 'f')
            return ch - 'a' + 10;
        else
            return -1;
    }

    //将字节数组转换成16进制字符串
    static QString ByteArrayToStr(const QByteArray & data)
    {
        QString tmp("");
        QString hex = data.toHex();
        auto sz = hex.length();
        for(int i = 0; i < sz; i+=2){
            tmp += hex.mid(i,2) + " ";
        }
        return tmp.trimmed().toUpper();
    }

    //16进制的字符串转换成10进制
    static int StrHexToDecimal(const QString & strHex)
    {
        bool ok;
        return strHex.toInt(&ok, 16);
    }

    //10进制字符串转换成10进制
    static int StrDecToDecimal(const QString & strDec)
    {
        bool ok;
        return strDec.toInt(&ok, 10);
    }

    //二进制字符串转换成10进制
    static int StrBinToDecimal(const QString & strBin)
    {
        bool ok;
        return strBin.toInt(&ok, 2);
    }


    static QString StrHexToStrBin(QString StrHex)
    {
        uchar decimal = StrHexToDecimal(strHex);
        return QString("%1").arg(QString::number(decimal, 2), 8, '0');//不足8位使用8位来进行补全
    }

    //十进制转换到2进制的一个字节
    static QString DecimalToStrBin1(int decimal)
    {
        return QString("%1").arg(QString::number(decimal, 2), 8, '0');//转换到8位的一个字节

    }

    //十进制转换到2进制两个字节
    static QString DecimalToStrBin2(int decimal)
    {
        return QString("%1").arg(QString::number(decimal, 2), 16, '0');
    }


    //计算校验码
    static uchar GetCheckCode(uchar data[], uchar len)
    {
        uchar temp = 0;
        for(uchar i = 0; i < len; ++i){
            temp += data[i];
        }
        return temp * 256;
    }

    //char 转换成uchar
    static uchar getUChar(char data)
    {
        uchar tmp;
        if(data > 127){
            tmp = data + 256;
        }else{
            tmp = data;
        }
        return tmp;
    }

    //方便使用的延时函数
    static void Sleep(int secs)
    {
        QTime dieTime = QTime::currentTime() + secs;
        while(QTime::currentTime() < dieTime)
            QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
    }

    //得到当前的路径
    static QString GetCurrentPath()
    {
        return QString(QCoreApplication::applicationDirPath() + "/");
    }

    //播放声音
    static void PlaySound(QString soundName)
    {
        QSound::play(soundName);
    }

    //设置系统的日期以及时间
    static void SetSystemDataTime(int year, int month, int day, int hour, int min, int sec)
    {
        QProcess p(0);
        p.start("cmd");
        p.waitForStarted();
        p.closeWriteChannel();
        p.waitForFinished(1000);
        p.close();

        p.start("cmd");
        p.waitForStarted();
        p.closeWriteChannel();
        p.waitForFinished(1000);
        p.close();
    }

    static void FormOnlyCloseInCenter(QWidget * frm)
    {
        QDesktopWidget desktop;
        int screenX = desktop.availableGeometry().width();
        int screenY = desktop.availableGeometry().height() - 40;
        int frmX = frm->width();
        int frmY = frm->height();
        QPoint movePoint(screenX/2 - frmX/2, screenY/2 - frmY/2);
        frm->move(movePoint);

        frm->setFixedSize(frmX, frmY);
        frm->setWindowFlags(Qt::WindowCloseButtonHint);

    }


    static void FormInCenter(QWidget * frm)
    {
        int screenX = qApp->desktop()->width();
        int screenY = qApp->desktop()->height()-60;
        int wndX = frm->width();
        int wndY = frm->height();
        QPoint movePoint((screenX-wndX)/2, (screenY - wndY)/2);
        frm->move(movePoint);
    }


    //窗体没有最大化按钮
    static void FormNoMaxButton(QWidget * frm)
    {
        frm->setWindowFlags(Qt::WindowMinimizeButtonHint);
    }

    //窗体直邮关闭按钮
    static void FormOnlyCloseButton(QWidget * frm)
    {
        frm->setWindowFlags(Qt::WindowCloseButtonHint);
    }

    //禁止窗口改变大小
    static void FormNotResize(QWidget * frm)
    {
        frm->setFixedSize(frm->width(), frm->height());
    }

    //获取桌面的大小
    static QSize GetDeskTopSize()
    {
        QDesktopWidget desktop;
        return QSize(desktop.availableGeometry().width(), desktop.availableGeometry().height());
    }

    //获取选取的文件
    static QString GetFileName(const QString & filter) //filter标明的是想要选中的文件的类型
    {
        return QFileDialog::getOpenFileName(NULL, "选择文件", QCoreApplication::applicationDirPath(), filter);
    }

    //获取选取的文件的集合
    static QStringList GetFileNames(const QString & filter)
    {
        return QFileDialog::getOpenFileNames(NULL, "选择文件", QCoreApplication::applicationDirPath(), filter);
    }

    //获取选择的目录
    static QString GetFolderName()
    {
        return QFileDialog::getExistingDirectory();
    }

    //获取文件名及其扩展名
    static QString GetFileNameWithExtension(QString strFilePath)
    {
            QFileInfo fileInfo(strFilePath);
            return fileInfo.fileName();//这里返回的文件名字会带有扩展名
    }

    //获取选择的文件夹中的文件
    static QStringList GetFolderFileNames(QStringList filter)
    {
        QStringList fileList;
        QString strFolder = QFileDialog::getExistingDirectory();
        if(!(strFolder.length() == 0)){
            QDir myFolder(strFolder);
            if(myFolder.exists()){
                fileList = myFolder.entryList(filder);
            }
        }
        return fileList;
    }

    //查看文件是否存在
    static bool FileIsExist(QString strFile)
    {
        QFile tmpFile(strFile);
        return tmpFile.exists();
    }

    //复制文件
    static bool CopyFile(const QString & sourceFile, const QString & targetFile)
    {
        if(FileIsExist(targetFile)){
            int ret = QMessageBox::information(NULL, "提示", "文件已经存在，是否替换？", QMessageBox::Yes | QMessageBox::No);
            if(ret != QMessageBox::Yes){
                return false;
            }
            return QFile::copy(sourceFile, targetFile);
        }
    }





};


#endif // MYHELPER

