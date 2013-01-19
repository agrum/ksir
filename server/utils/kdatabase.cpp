#include "kdatabase.h"

kDatabase::kDatabase():
	m_set(false)
{
	*(QSqlDatabase*) this = QSqlDatabase::addDatabase("QMYSQL");
}

void kDatabase::login()
{
	if(m_set)
		return;

	QString username;
	QString password;
	QTextStream input(stdin, QIODevice::ReadOnly);
	QTextStream output(stdout, QIODevice::WriteOnly);

	output << "Database loggin" << endl;

	//username
	output << "_username : ";
	output.flush();
	username = input.readLine();

#ifdef WIN32
	string s;
	HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
	DWORD mode = 0;
	GetConsoleMode(hStdin, &mode);
	SetConsoleMode(hStdin, mode & (~ENABLE_ECHO_INPUT));

	string s;
	getline(cin, s);
	password = QString::fromStdString(s);

	SetConsoleMode(hStdin, mode);
	tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
#elif unix
	//password
	cout << "_password : ";
	string s;
	termios oldt;
	tcgetattr(STDIN_FILENO, &oldt);
	termios newt = oldt;
	newt.c_lflag &= ~ECHO;
	tcsetattr(STDIN_FILENO, TCSANOW, &newt);

	getline(cin, s);
	password = QString::fromStdString(s);
#endif

	setUserName(username);
	setPassword(password);
}

void kDatabase::readXml(const QString& p_tag, const QDomElement& p_node)
{
	if( p_tag == "host" )
		setHostName(p_node.text());
	else if( p_tag == "dbname" )
		setDatabaseName(p_node.text());
	else if( p_tag == "user" ){
		m_set = true;
		setUserName(p_node.text());
	}
	else if( p_tag == "password" )
		setPassword(p_node.text());
}
