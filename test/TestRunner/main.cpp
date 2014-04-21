
/*!
	\file

	\author Igor Mironchik (igor.mironchik at gmail dot com).

	Copyright (c) 2012 Igor Mironchik

	Permission is hereby granted, free of charge, to any person
	obtaining a copy of this software and associated documentation
	files (the "Software"), to deal in the Software without
	restriction, including without limitation the rights to use,
	copy, modify, merge, publish, distribute, sublicense, and/or sell
	copies of the Software, and to permit persons to whom the
	Software is furnished to do so, subject to the following
	conditions:

	The above copyright notice and this permission notice shall be
	included in all copies or substantial portions of the Software.

	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
	EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
	OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
	NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
	HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
	WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
	FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
	OTHER DEALINGS IN THE SOFTWARE.
*/

// Qt include.
#include <QtCore/QProcess>
#include <QtCore/QObject>
#include <QtCore/QCoreApplication>
#include <QtCore/QTimer>
#include <QtCore/QStringList>
#include <QtCore/QDir>
#include <QtCore/QTextStream>
#include <QtCore/QString>
#include <QtCore/QFileInfo>


//
// TestRunner
//

class TestRunner
	:	public QObject
{
	Q_OBJECT

public:
	TestRunner( char * appName )
	{
		QDir dir( "." );
		init( dir );
        m_tests.removeOne( QDir::toNativeSeparators(
            dir.absoluteFilePath( appName ) ) );
	}

	~TestRunner()
	{
	}

public slots:
	void runTests()
	{
		QTextStream stream( stdout );

		foreach( QString testApp, m_tests )
		{
			QProcess process;
			process.setWorkingDirectory( QFileInfo( testApp ).absolutePath() );
			process.start( testApp );
			process.waitForFinished();
			stream << process.readAllStandardOutput();
			stream << process.readAllStandardError();

			if( process.exitCode() != 0 )
				break;
		}

		QCoreApplication::quit();
	}

private:
	void init( QDir & dir )
	{
		dir.setFilter( QDir::Files | QDir::NoSymLinks | QDir::Executable );
		QStringList executables = dir.entryList();

		foreach( QString fileName, executables )
            m_tests.append( QDir::toNativeSeparators(
                dir.absoluteFilePath( fileName ) ) );

		dir.setFilter( QDir::Dirs | QDir::NoSymLinks );

		QStringList searchDirectories = dir.entryList();
		searchDirectories.removeOne( "." );
		searchDirectories.removeOne( ".." );

		foreach( QString searchPath, searchDirectories )
		{
			dir.cd( searchPath );
			init( dir );
			dir.cd( ".." );
		}
	}

private:
	QStringList m_tests;
}; // class TestRunner


int main( int argc, char ** argv )
{
	QCoreApplication app( argc, argv );

	TestRunner testRunner( argv[ 0 ] );

	QTimer::singleShot( 0, &testRunner, SLOT( runTests() ) );

	return app.exec();
}

#include "main.moc"
