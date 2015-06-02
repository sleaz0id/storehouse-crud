#include "./Header.h"

int lista_klientow (void) {
    int i;
    int pusta = 0;
    cout << endl << "Lista klientów:" << endl << endl;
    for (i = 1; i < N; i++) {
        if (!klienci[i].nazwa.empty()) {
            cout << i << ". " << klienci[i].nazwa << "   " << "grupa: " << klienci[i].grupa << "   " << "NIP: " << klienci[i].nip << "   " << "saldo: " << klienci[i].saldo << " PLN" << "   " << "rabat: " << klienci[i].rabat << "%" << endl;
            pusta = 1;
        }
    }
    if (!pusta) {
        cout << "Lista klientów jest pusta." << endl
        << endl << "Naciśnij klawisz enter, aby konynuować" << endl;
        cin.ignore();
        cin.get();
        return 1;
    } else {
        cout << endl;
        return 0;
    }
}

void dodaj_klienta (void) {
    string nazwa, grupa, nip;
    cout << "Podaj nazwę klienta, którego chcesz dodać:" << endl;
    cin >> nazwa;
	cout << "Podaj grupę klienta" << endl;;
	cin >> grupa;
	cout << "Podaj NIP klienta:" << endl;
	cin >> nip;
    int i;
    for (i = 1; i < N; i++)
    {
        if (klienci[i].nazwa == nazwa) {
            cout << "Nazwa klienta istnieje już w bazie." << endl;
            break;
        } else if (klienci[i].nazwa.empty()) {
            klienci[i].nazwa = nazwa;
            klienci[i].id_klienta = i;
            klienci[i].grupa = grupa;
            klienci[i].nip = nip;
            break;
        }
    }
}

int edytuj_klienta (void) {
	string s_temp;
	int id;
    int pom = 0;
    if (lista_klientow()) {
        return 1;
    }
    cout << "Podaj ID klienta, którego chcesz edytować:" << endl;
    cin >> id;
    int i;
    for (i = 1; i < N; i++) {
        if (klienci[i].id_klienta == id) {
            pom = 1;
            cout << "Edycja danych klienta o id #" << i << ":" << endl;
            cout << "Podaj nową nazwę klienta (aktualna nazwa: " << klienci[i].nazwa << "):" << endl;
			cin.ignore();
			getline(cin, s_temp);
			if (s_temp == "") {
				cout << "(" << klienci[i].nazwa << ")" << endl;
			}
			else {
				klienci[i].nazwa = s_temp;
				s_temp = "";
			}
            cout << "Podaj nową nazwę grupy (aktualna grupa: " << klienci[i].grupa << "):" << endl;
            cin >> klienci[i].grupa;
            cout << "Podaj nowy nr NIP (aktualny nip: " << klienci[i].nip << "):" << endl;
            cin >> klienci[i].nip;
        }
    }
    if (!pom) {
        cout << "Nie znaleziono klienta o podanym ID." << endl << "Naciśnij klawisz enter, aby konynuować" << endl;
        cin.ignore();
        cin.get();
    } else {
        lista_klientow();
        cout << "Naciśnij klawisz enter, aby konynuować" << endl;
        cin.ignore();
        cin.get();
    }
    return 0;
}

int usun_klienta (void) {
    if (lista_klientow()) {
        return 1;
    }
    int id;
    int pom = 0;
    char odp;
    cout << "Podaj ID, którego chcesz usunąć z bazy: " << endl;
    cin >> id;
    int i;
    for (i = 1; i < N; i++) {
        if (klienci[i].id_klienta == id) {
            pom = 1;
            cout << "Czy na pewno chcesz usunąć wpis klienta o nazwie " << klienci[i].nazwa << "? (T/n)" << endl;
            cin >> odp;
            if (odp == 'T') {
                klienci[i].nazwa = "";
                klienci[i].grupa = "";
                klienci[i].nip = "";
                klienci[i].id_klienta = 0;
                klienci[i].rabat = 0;
                klienci[i].saldo = 0;
                cout << "Wpis klienta został usunięty." << endl;
                break;
            } else {
                cout << "Usuwanie anulowane.";
                break;
            }
        }
    }
    if (!pom) {
        cout << "Nie znaleziono wpisu o podanej nazwie klienta." << endl;
    }
    return 0;
}

void rabaty (void) {
    int wybor, id, pom = 0;
	string grupa, temp;
	int rabat;
	cout << "Zmień wysokość rabatu:" << endl <<
			"1. Pojedynczego klienta" << endl <<
			"2. Grupy klinetów" << endl;
	cin >> temp;
	wybor = atoi(temp.c_str());

	switch (wybor) {
	case 1:
		if (!lista_klientow()) {
			cout << "Podaj ID klienta, którego rabat ma zostać zmieniony: " << endl;
			cin >> id;
			cout << "Podaj wysokość rabatu (np. 5%):" << endl;
			cin >> rabat;
			int i;
			for (i = 1; i < N; i++) {
				if (klienci[i].id_klienta == id) {
					pom = 1;
					cout << "Podaj wysokość rabatu (np. 5%):" << endl;
					klienci[i].rabat = rabat;
				}
			}
			if (!pom) {
				cout << "Nie znaleziono wpisu o podanym ID klienta." << endl;
			}
			else {
				lista_klientow();
				cout << "Naciśnij klawisz enter, aby konynuować" << endl;
				cin.ignore();
				cin.get();
			}
		}
		break;
	case 2:
		if (!lista_klientow()) {
			cout << "Podaj nazwę grupy, której ma zostać przyznany rabat" << endl;
			cin >> grupa;
			cout << "Podaj wysokość rabatu (np. 5%):" << endl;
			cin >> rabat;
			int i;
			for (i = 1; i < N; i++) {
				if (klienci[i].grupa == grupa) {
					pom = 1;
					klienci[i].rabat = rabat;
				}
			}
			if (!pom) {
				cout << "Nie znaleziono grupy o podanej nazwie." << endl;
			}
			else {
				lista_klientow();
				cout << "Naciśnij klawisz enter, aby konynuować" << endl;
				cin.ignore();
				cin.get();
			}
		}
		break;
	default:
		cout << "Błędny wybór." << endl;
		break;
	}
}
