#include "src/lib/Base.h"
#include "src/lib/PrivDerived.h"
#include "src/lib/ProtDerived.h"
#include "src/lib/PublicDerived.h"
#include "src/lib/dPriv.h"
#include "src/lib/dProt.h"
#include "src/lib/dPublic.h"
#include <iostream>
#include <string>
using namespace std;

int main(void) {
    Base* b = new Base( );
    PrivDerived* privd = new PrivDerived( );
    ProtDerived* protd = new ProtDerived( );
    PublicDerived* publicd = new PublicDerived( );
    dPriv* dpriv = new dPriv( );
    dProt* dprot = new dProt( );
    dPublic* dpublic = new dPublic( );

    cout << "Base" << endl;
    cout << b->getPrivB() << endl;
    cout << b->getProtB() << endl;
    cout << b->publicB << endl;

    cout << "Private Derived" << endl;
    cout << privd->showMePrivB() << endl;
    cout << privd->showMeProtB() << endl;
    cout << privd->showMePublicB() << endl;


    cout << "Protected Derived" << endl;
    cout << protd->showMePrivB() << endl;
    cout << protd->showMeProtB() << endl;
    cout << protd->showMePublicB() << endl;

    cout << "Public Derived" << endl;
    cout << publicd->getPrivB() << endl;
    cout << publicd->getProtB() << endl;
    cout << publicd->publicB << endl;

    cout << "Derived Private" << endl;
    cout << dpriv->showMePrivB() << endl;
    cout << dpriv->showMeProtB() << endl;
    cout << dpriv->showMePublicB() << endl;

    cout << "Derived Protected" << endl;
    cout << dprot->showMePrivB() << endl;
    cout << dprot->showMeProtB() << endl;
    cout << dprot->showMePublicB() << endl;

    cout << "Derived Public" << endl;
    cout << dpublic->getPrivB() << endl;
    cout << dpublic->getProtB() << endl;
    cout << dpublic->publicB << endl;

    return 0;
}
