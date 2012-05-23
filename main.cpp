#include "switch.hpp"

/** --------------------------------------------------------------------------------------------------------------- **/

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QNetworkProxyFactory::setUseSystemConfiguration(true);
    Switch window;
    window.show();

    return app.exec();
}

/** --------------------------------------------------------------------------------------------------------------- **/
