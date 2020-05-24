#include "smtp.h"
#include "gesprofil.h"
#include "ui_gesprofil.h"



Smtp::Smtp( const QString &user, const QString &pass, const QString &host, int port, int timeout )
{
    socket = new QSslSocket(this);

    connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()));
    connect(socket, SIGNAL(connected()), this, SLOT(connected() ) );
    connect(socket, SIGNAL(error(QAbstractSocket::SocketError)), this,SLOT(errorReceived(QAbstractSocket::SocketError)));
    connect(socket, SIGNAL(stateChanged(QAbstractSocket::SocketState)), this, SLOT(stateChanged(QAbstractSocket::SocketState)));
    connect(socket, SIGNAL(disconnected()), this,SLOT(disconnected()));


    this->user = user;
    this->pass = pass;

    this->host = host;
    this->port = port;
    this->timeout = timeout;


}


void Smtp::sendMail(const QString &from, QString to, const QString &subject,int x)
{

    message = "To: " + to + "\n";
    message.append("From: " + from + "\n");
    message.append("Subject: " "Bienvenue à notre POSTE" "\n");

    //Let's intitiate multipart MIME with cutting boundary "frontier"
    message.append("MIME-Version: 1.0\n");
    message.append("Content-Type: multipart/mixed; boundary=frontier\n\n");



    message.append( "--frontier\n" );
    message.append( "Content-Type: text/html\n\n" );  //Uncomment this for HTML formating, coment the line below
   // message.append("<html><body><h1 style=""font-size:300%;"">This is a heading</h1><p style=""font-size:160%;"">This is a paragraph.</p>");
    message.append("<html><head></head><body><center>"+QString("&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<font size=""10"" color =""Green"">Bienvenue cher salarié à notre poste.</font><br /> <br /> "));





  message.append("<center>"+QString("&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<font size=""4"" color =""Black"">Bienvenue cher salarié à notre poste. Vous trouverez ci-dessous vos coordonnées, ainsi que votre e-mail et mot de passe qui vous permetteront à se connecter à notre application! Bon Travail :)</font><br /></html>"));


   // message.append( "Content-Type: text/plain\n\n" );
    message.append("\n\n");
    message.append("<table border=0.5><tr>");
    message.append("<td>"+QString("  ")+"&nbsp;&nbsp;<font color =""blue""  size=""3"">ID</font>&nbsp;&nbsp;"+"</td>");
    message.append("<td>"+QString("  ")+"&nbsp;&nbsp;<font color =""blue""  size=""3"">Nom</font>&nbsp;&nbsp;"+"</td>");
    message.append("<td>"+QString("&nbsp;&nbsp;<font color =""blue""  size=""3"">Prénom</font>&nbsp;&nbsp;")+"</td>");
    message.append("<td>"+QString("&nbsp;&nbsp;<font color =""blue""  size=""3"">E-mail</font>&nbsp;&nbsp;")+"</td>");
    message.append("<td>"+QString("&nbsp;&nbsp;<font color =""blue""  size=""3"">Mot de passe</font>&nbsp;&nbsp;")+"</td>");
    QSqlQuery * query=new QSqlQuery();
    query->exec("SELECT ID,NOM,PRENOM,ADRESSE,MDP FROM PROFIL where adresse='"+to+"'");
    while(query->next())
    {

        message.append("<tr><td>");
        message.append("&nbsp;&nbsp;<font color =""black"" size= ""3"">"+query->value(0).toString()+"&nbsp;&nbsp;");
        message.append("</td><td>");
        message.append("&nbsp;&nbsp;<font color =""black""  size=""3"">"+query->value(1).toString()+"&nbsp;&nbsp;");
        message.append("</td><td>");
        message.append("&nbsp;&nbsp;<font color =""black""  size=""3"">"+query->value(2).toString()+"&nbsp;&nbsp;");
        message.append("</td><td>");
        message.append("&nbsp;&nbsp;<font color =""black""  size=""3"">"+query->value(3).toString()+"&nbsp;&nbsp;");
        message.append("</td><td>");
        message.append("&nbsp;&nbsp;<font color =""black"" size= ""3"">"+query->value(4).toString()+"&nbsp;&nbsp;");
        message.append("</td><td>");
    }

    message.append("</table></center><body></html>");

    message.append( "--Smart Post 2A10--\n" );

    message.replace( QString::fromLatin1( "\n" ), QString::fromLatin1( "\r\n" ) );
    message.replace( QString::fromLatin1( "\r\n.\r\n" ),QString::fromLatin1( "\r\n..\r\n" ) );

    this->from = from;
    rcpt = to;
    state = Init;
    socket->connectToHostEncrypted(host, port); //"smtp.gmail.com" and 465 for gmail TLS
    if (!socket->waitForConnected(timeout)) {
         qDebug() << socket->errorString();
     }

    t = new QTextStream( socket );



}

Smtp::~Smtp()
{
    delete t;
    delete socket;
}
void Smtp::stateChanged(QAbstractSocket::SocketState socketState)
{

    qDebug() <<"stateChanged " << socketState;
}

void Smtp::errorReceived(QAbstractSocket::SocketError socketError)
{
    qDebug() << "error " <<socketError;
}

void Smtp::disconnected()
{

    qDebug() <<"disconneted";
    qDebug() << "error "  << socket->errorString();
}

void Smtp::connected()
{
    qDebug() << "Connected ";
}

void Smtp::readyRead()
{

     qDebug() <<"readyRead";
    // SMTP is line-oriented

    QString responseLine;
    do
    {
        responseLine = socket->readLine();
        response += responseLine;
    }
    while ( socket->canReadLine() && responseLine[3] != ' ' );

    responseLine.truncate( 3 );

    qDebug() << "Server response code:" <<  responseLine;
    qDebug() << "Server response: " << response;

    if ( state == Init && responseLine == "220" )
    {
        // banner was okay, let's go on
        *t << "EHLO localhost" <<"\r\n";
        t->flush();

        state = HandShake;
    }
    //No need, because I'm using socket->startClienEncryption() which makes the SSL handshake for you

    else if (state == HandShake && responseLine == "250")
    {
        socket->startClientEncryption();
        if(!socket->waitForEncrypted(timeout))
        {
            qDebug() << socket->errorString();
            state = Close;
        }


        //Send EHLO once again but now encrypted

        *t << "EHLO localhost" << "\r\n";
        t->flush();
        state = Auth;
    }
    else if (state == Auth && responseLine == "250")
    {
        // Trying AUTH
        qDebug() << "Auth";
        *t << "AUTH LOGIN" << "\r\n";
        t->flush();
        state = User;
    }
    else if (state == User && responseLine == "334")
    {
        //Trying User
        qDebug() << "Username";
        //GMAIL is using XOAUTH2 protocol, which basically means that password and username has to be sent in base64 coding
        //https://developers.google.com/gmail/xoauth2_protocol
        *t << QByteArray().append(user).toBase64()  << "\r\n";
        t->flush();

        state = Pass;
    }
    else if (state == Pass && responseLine == "334")
    {
        //Trying pass
        qDebug() << "Pass";
        *t << QByteArray().append(pass).toBase64() << "\r\n";
        t->flush();

        state = Mail;
    }
    else if ( state == Mail && responseLine == "235" )
    {
        // HELO response was okay (well, it has to be)

        //Apperantly for Google it is mandatory to have MAIL FROM and RCPT email formated the following way -> <email@gmail.com>
        qDebug() << "MAIL FROM:<" << from << ">";
        *t << "MAIL FROM:<" << from << ">\r\n";
        t->flush();
        state = Rcpt;
    }
    else if ( state == Rcpt && responseLine == "250" )
    {
        //Apperantly for Google it is mandatory to have MAIL FROM and RCPT email formated the following way -> <email@gmail.com>
        *t << "RCPT TO:<" << rcpt << ">\r\n"; //r
        t->flush();
        state = Data;
    }
    else if ( state == Data && responseLine == "250" )
    {

        *t << "DATA\r\n";
        t->flush();
        state = Body;
    }
    else if ( state == Body && responseLine == "354" )
    {

        *t << message << "\r\n.\r\n";
        t->flush();
        state = Quit;
    }
    else if ( state == Quit && responseLine == "250" )
    {

        *t << "QUIT\r\n";
        t->flush();
        // here, we just close.
        state = Close;
        emit status( tr( "Message sent" ) );
    }
    else if ( state == Close )
    {
        deleteLater();
        return;
    }
    else
    {
        // something broke.
        QMessageBox::warning( 0, tr( "Qt Simple SMTP client" ), tr( "Unexpected reply from SMTP server:\n\n" ) + response );
        state = Close;
        emit status( tr( "Failed to send message" ) );
    }
    response = "";
}

