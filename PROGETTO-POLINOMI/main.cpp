#include <iostream>
#include <cmath> // Per abs() e pow()
#include <conio.h> // Per getch()
#include "graphics2.h" // Per le funzioni grafiche
#include <cstdlib> // Per tolower()
#include <windows.h> // Per ShowWindow();
#include <string> // Per to_string()
using namespace std;

// Costanti per stabilire il range massimo degli array
const int MAX1 = 4, MAX2 = 7;

// Costanti per la dimensione della finestra per la grafica
const int WIDTH = 667, HEIGHT = 667;

// Somma tra due polinomi
void sum(int poli1[MAX1], int poli2[MAX1], int poliResult[MAX1]) {
    for (int i = 0; i < MAX1; i++) poliResult[i] = 0;
    
    for (int i = MAX1 - 1; i >= 0; i--) poliResult[i] = poli1[i] + poli2[i];
}

// Differenza tra due polinomi
void subtr(int poli1[MAX1], int poli2[MAX1], int poliResult[MAX1]) {
    for (int i = 0; i < MAX1; i++) poliResult[i] = 0;
    
    for (int i = MAX1 - 1; i >= 0; i--) poliResult[i] = poli1[i] - poli2[i];
}

// Moltiplicazione tra due polinomi
void multi(int poli1[MAX1], int poli2[MAX1], int poliResult[MAX2]) {
    for (int i = 0; i < MAX2; i++) poliResult[i] = 0;

    for (int i = MAX1 - 1; i >= 0; i--) {
        for (int j = MAX1 - 1; j >= 0; j--) {
            if (poli1[i] != 0 && poli2[j] != 0) 
                poliResult[i + j] += poli1[i] * poli2[j];
        }
    }
}

// Soluzioni di un polinomio di secondo grado
void quadraticFormula(int a, int b, int c) {
    int delta = pow(b, 2) - 4 * a * c;
    int x1, x2;

    if (delta > 0) {
        x1 = (-b + sqrt(delta)) / (2 * a);
        x2 = (-b - sqrt(delta)) / (2 * a);

        cout << "\nx(1) = " << "\033[1m" << x1 <<"\033[0m";
        cout << "\nx(2) = " << "\033[1m" << x2 <<"\033[0m";
    } else if (delta == 0) {
        x1 = -b / (2 * a);

        cout << "\nx(1) e x(2) = " << "\033[1m" << x1 << "\033[0m";
    } else {
        cout << "\n\033[31mNon sono presenti soluzioni per questo polinomio!\033[0m";
    }
}

// Soluzioni di un polinomio di primo grado
void firstDegreeEquation(int tN, int tP) {
    bool isInconsistent = false, isIdentity = false;

    if (tN > 0 && tP > 0) tN = -tN;
    else if (tN < 0 && tP > 0) tN = abs(tN);
    else if ((tN > 0 && tP < 0) || (tN < 0 && tP < 0)) tP = abs(tP);
    else if (tN == 0 && tP == 0) isInconsistent = true;
    else if (tN != 0 && tP == 0) isIdentity = true;

    if (isIdentity) cout << "\n\033[31mIl polinomio risulta indeterminato!\033[0m";
    else if (isInconsistent) cout << "\n\033[31mIl polinomio risulta impossibile!\033[0m";
    else cout << "\nx(1) = " << "\033[1m" << tN / tP << "\033[0m";
}

// Punti di intersezione per grado 2
void pointOfIntersectionForSecond(int poli1[MAX1], int poliResult[MAX1], bool isGraphic) {
    double x1, x2, y1 = 0, y2 = 0, delta, a = poliResult[MAX1 - 2], b = poliResult[MAX1 - 3], c = poliResult[0];

    delta = pow(b, 2) - 4 * a * c;

    if (delta > 0) {
        x1 = (-b + sqrt(delta)) / (2 * a);
        x2 = (-b - sqrt(delta)) / (2 * a);

        for (int i = MAX1 - 2; i >= 0; i--) {
            if (poli1[i] != 0) {
                // i deve essere diverso da zero per evitare situazione 0^0
                if (i != 0) {
                    y1 += pow(x1, i) * poli1[i];
                    y2 += pow(x2, i) * poli1[i];
                } else {
                    y1 += poli1[i];
                    y2 += poli1[i];
                }
            }
        }

        if (isGraphic) {
            circle(WIDTH / 2 + x1 * 33, HEIGHT / 2 + y1 * 33 * - 1, 5); 
	        circle(WIDTH / 2 + x2 * 33, HEIGHT / 2 + y2 * 33 * - 1, 5);
        } else {
            cout << "1: (x, y) = " << "(" << "\033[1m" << x1 << ", " << y1 << "\033[0m" << ")" << "\n";
            cout << "2: (x, y) = " << "(" << "\033[1m" << x2 << ", " << y2 << "\033[0m" << ")";
        }
        
    } else if (delta == 0) {
        x1 = -b / (2 * a);

        for (int i = MAX1 - 2; i >= 0; i--) {
            if (poli1[i] != 0) {
                if (i != 0) y1 += pow(x1, i) * poli1[i];
                else  y1 += poli1[i];
            }
        }

        if (isGraphic)
            circle(WIDTH / 2 + x1 * 33, HEIGHT / 2 + y1 * 33 * - 1, 5);
        else 
            cout << "1: (x, y) = " << "(" << "\033[1m" << x1 << ", " << y1 << "\033[0m" << ")" << "\n";
    } else {
        cout << "\033[31mI due polinomi non si intersecano in nessun punto!\033[0m";
    }
}

// Punti di intersezione per grado 1
void pointOfIntersectionForFirst(int poli1[MAX1], int poli2[MAX1], int poliResult[MAX1], bool isGraphic) {
    bool isInconsistent = false, isIdentity = false;
    double tN = poliResult[0], tP = poliResult[MAX1 - 3], x, y = 0;

    if (tN > 0 && tP > 0) tN = -tN;
    else if (tN < 0 && tP > 0) tN = abs(tN);
    else if ((tN > 0 && tP < 0) || (tN < 0 && tP < 0)) tP = abs(tP);
    else if (tN != 0 && tP == 0) isInconsistent = true;
    else if (tN == 0 && tP == 0) isIdentity = true;

    if (isIdentity) {
        if (!isGraphic) {
            if (poli1[MAX1 - 2] != 0 && poli2[MAX1 - 2] != 0)
                cout << "\033[31mLe due parabole sono coincidenti!\033[0m";
            else
                cout << "\033[31mLe due rette sono coincidenti!\033[0m";
        }
    } else if (isInconsistent) {
        if (!isGraphic) {
            if (poli1[MAX1 - 2] != 0 && poli2[MAX1 - 2] != 0)
                cout << "\033[31mLe due parabole non si toccano in nessun punto!\033[0m";
            else
                cout << "\033[31mLe due rette sono parallele!\033[0m";
        }
    } else {
        x = tN / tP;

        for (int i = MAX1 - 2; i >= 0; i--) {
            if (poli1[i] != 0) {
                if (i != 0) y += pow(x, i) * poli1[i];
                else y += poli1[i];
            }
        }

        if (isGraphic)
            circle(WIDTH / 2 + x * 33, HEIGHT / 2 + y * 33 * - 1, 5);
        else
            cout << "1: (x, y) = " << "(" << "\033[1m" << x << ", " << y << "\033[0m" << ")" << "\n";
    }
}

// Rappresentazione grafica del polinomio
void graphicRapr(int poli[MAX1]) {
    double preX, preY;

    for (double x = -15; x <= 15; x += 0.2) {
        double y = 0;

        for (int i = MAX1 - 1; i >= 0; i--) {
            if (poli[i] != 0) {
                if (i != 0) y += pow(x, i) * poli[i];
                else y += poli[i];
            }
        }

        // Inserisci i punti all'interno del grafico
        if (WIDTH / 2 + x * 33 < WIDTH && HEIGHT / 2 + y * 33 * - 1 < HEIGHT && WIDTH / 2 + preX * 33 < WIDTH && HEIGHT / 2 + preY * 33 * - 1 < HEIGHT) {
            if (x > -15)
                line(WIDTH / 2 + x * 33, HEIGHT / 2 + y * 33 * - 1, WIDTH / 2 + preX * 33, HEIGHT / 2 + preY * 33 * - 1);	
        } 

        preX = x;
        preY = y;
    }
}

// Stampa dei polinomi
void printPoli(int poli[MAX2], int maxDegree) {
    bool isAllZero = true;

    for (int i = maxDegree; i >= 0; i--) {
        if (poli[i] != 0) {
            isAllZero = false;
            break;
        }
    }

    if (isAllZero) {
        cout << "\033[1m" << 0 << "\033[0m";
    } else {
        if (poli[maxDegree] != 0) {
            cout << (poli[maxDegree] > 0 ? "+" : "-");
        }
        
        cout << "\033[1m";
        for (int i = maxDegree; i >= 0; i--) {
            if (poli[i] != 0) {
                if (i != 0) cout << abs(poli[i]) << "x^" << i;
                else cout << abs(poli[i]);
            }
            
            if (i != 0 && poli[i - 1] != 0) cout << (poli[i - 1] > 0 ? " +" : " -");
        }
        cout << "\033[0m";
    }
}

// controlla input
bool inputChecking(int maxDegree) {
    // Controllo in caso l'utente metta un valore diverso da un numero
    if (cin.fail()) {
        cin.clear(); // Elimina l'errore
        cin.ignore(1000, '\n'); // Consuma tutti i caratteri nel buffer fino a \n
        return true; 
    } 
    
    if (maxDegree > 3 || maxDegree < 0) return true;

    return false;
}

// Stampa dei polinomi nella finestra grafica
string printPoliGraphic(int poli[MAX1], int maxDegree) {
    string polynomial = "";
    bool isAllZero = true;

    polynomial += "P(1) = ";

    for (int i = maxDegree; i >= 0; i--) {
        if (poli[i] != 0) {
            isAllZero = false;
            break;
        }
    }

    if (isAllZero) {
        polynomial += "0";
        return polynomial;
    } else {
        if (polynomial[maxDegree] != 0)
            polynomial += (poli[maxDegree] > 0) ? "+" : "-";
        
        for (int i = maxDegree; i >= 0; i--) {
            if (poli[i] != 0) {
                if (i != 0)
                    polynomial += to_string(abs(poli[i])) + "x^" + to_string(i);
                else
                    polynomial += to_string(abs(poli[i]));
            }
            
            if (i != 0 && poli[i - 1] != 0)
                polynomial += poli[i - 1] > 0 ? " +" : " -";
        }

        return polynomial;
    }
}

int main() {
    // Variabili per stabilire i gradi massimi dei vari polinomi
    int maxDegree1, maxDegree2;

    // Array che contengono i valori dei due polinomi inseriti dall'utente
    int polynomial1[MAX1]{0}, polynomial2[MAX1]{0};

    // Array che contengono i valori delle operazioni
    int sumPolynomial[MAX1]{0}, subtrPolynomial[MAX1]{0}, multiPolynomial[MAX2]{0};

    // Variabili per la creazione della finestra per la grafica
    int graphDriver = 0, graphMode = 0;

    // Variabili per la gestione degli errori e del corretto funzionamento del programma
    char option, userExit, userChoice;
    bool isFirstTime = true, isRunning = true;

    // Considera solo 3 numeri significativi per i numeri decimali
    cout.precision(3); 

    cout << "\033[36m  _____   ____  _      _____ _   _  ____  __  __ _____\n";
    cout << " |  __ \\ / __ \\| |    |_   _| \\ | |/ __ \\|  \\/  |_   _|\n";
    cout << " | |__) | |  | | |      | | |  \\| | |  | | \\  / | | |  \n";
    cout << " |  ___/| |  | | |      | | | . ` | |  | | |\\/| | | |  \n";
    cout << " | |    | |__| | |____ _| |_| |\\  | |__| | |  | |_| |_ \n";
    cout << " |_|     \\____/|______|_____|_| \\_|\\____/|_|  |_|_____|\n";
    cout << "          [ PROGRAMMA PER RISOLVERE I POLINOMI ]\n";
    cout << "-------------------------------------------------------\033[0m\n\n";

    cout << "PROGRAMMA FATTO DA:\n";
    cout << " - EDOSA EZEKIEL\n";
    cout << " - GAMBERA GABRIELE\n";
    cout << " - CAMMARATA GABRIELE\n\n";

    cout << "\033[4mPremere qualsiasi tasto per continuare...\033[0m";
    getch();
    system("cls");

    while (isRunning) {
        if (isFirstTime) {
            cout << "\033[36m" << "---------------------------------------------------------------------------------" << "\033[0m\n";
            cout << "\033[36m|"<< "\033[1m                        PRIMA ACQUISIZIONE DEI POLINOMI                        " << "\033[1m|\033[0m\n";
            cout << "\033[36m" << "---------------------------------------------------------------------------------" << "\033[0m\n\n";

            // Controllo input del grado massimo del primo polinomio
            do {
                cout << "\033[3mInserisci il grado massimo del primo polinomio:       \033[0m";
                cin >> maxDegree1;

                if (cin.fail())
                    cout << "\033[31mAttenzione! Il programma non accetta caratteri o altro, ma solo NUMERI! Riprova!\033[0m\n";
                else if (maxDegree1 > 3 || maxDegree1 < 0)
                    cout << "\033[31mIl grado massimo del polinomio deve essere compreso tra 0 e 3, riprova!\033[0m\n";

            } while (inputChecking(maxDegree1));

            // Gestione input del primo polinomio
            for (int i = maxDegree1; i >= 0; i--) {
                if (i != 0) {
                    do {
                        cout << "\033[3m\nInserisci il coefficiente di grado x^" << i << ":       \033[0m";
                        cin >> polynomial1[i];

                        if (cin.fail())
                            cout << "\033[31mAttenzione! Il programma non accetta caratteri o altro, ma solo NUMERI! Riprova!\033[0m\n";
                    } while (inputChecking(0));
                } else {
                    do {
                        cout << "\033[3m\nInserisci il termine noto:       \033[0m";
                        cin >> polynomial1[i];

                        if (cin.fail()) {
                            cout << "\033[31mAttenzione! Il programma non accetta caratteri o altro, ma solo NUMERI! Riprova!\033[0m\n";
                        } 
                    } while (inputChecking(0));
                }
            }

            // Gestione output del primo polinomio
            cout << "\n\n\033[32mP(1): \033[0m";
            printPoli(polynomial1, maxDegree1);
            cout << "\n\n";

            // Controllo input del grado massimo del secondo polinomio
            do {
                cout << "\n\033[3mInserisci il grado massimo del secondo polinomio:       \033[0m";
                cin >> maxDegree2;
                
                if (cin.fail())
                    cout << "\033[31mAttenzione! Il programma non accetta caratteri o altro, ma solo NUMERI! Riprova!\033[0m\n";
                else if (maxDegree2 > 3 || maxDegree2 < 0)
                    cout << "\033[31mIl grado massimo del polinomio deve essere compreso tra 0 e 3, riprova!\033[0m\n";
                    
            } while (inputChecking(maxDegree2));
            
            // Gestione input del secondo polinomio
            for (int i = maxDegree2; i >= 0; i--) {
                if (i > 0) {
                    do {
                        cout << "\n\033[3mInserisci il coefficiente di grado x^" << i << ":       \033[0m";
                        cin >> polynomial2[i];

                        if (cin.fail())
                            cout << "\033[31mAttenzione! Il programma non accetta caratteri o altro, ma solo NUMERI! Riprova!\033[0m\n";
                        
                    } while (inputChecking(0));
                } else {
                    do {
                        cout << "\n\033[3mInserisci il termine noto:       \033[0m";
                        cin >> polynomial2[i];

                        if (cin.fail())
                            cout << "\033[31mAttenzione! Il programma non accetta caratteri o altro, ma solo NUMERI! Riprova!\033[0m\n";
                        
                    } while (inputChecking(0));
                }
            }
            
            // Gestione output del primo polinomio
            cout << "\n\n\033[32mP(2): \033[0m";
            printPoli(polynomial2, maxDegree2);

            cout << "\n\n\033[4mPremere qualsiasi tasto per continuare...\033[0m";
	        getch();
	        system("cls");
            isFirstTime = false;
        }
        
        cout << "\033[36m" << "---------------------------------------------------------------------------------" << "\033[0m\n";
        cout << "\033[36m|"<< "\033[1m                                 MENU PRINCIPALE                               " << "\033[1m|\033[0m\n";
        cout << "\033[36m" << "---------------------------------------------------------------------------------" << "\033[0m\n";
        cout << "\033[36m" << "|  \033[32m[1]\033[0m" << " Acquisizione dei polinomi                                                " << "\033[36m|\n";
        cout << "\033[36m" << "|  \033[32m[2]\033[0m" << " Somma di polinomi -> P(1) + P(2)                                         " << "\033[36m|\n";
        cout << "\033[36m" << "|  \033[32m[3]\033[0m" << " Differenza di polinomi -> P(1) - P(2)                                    " << "\033[36m|\n";
        cout << "\033[36m" << "|  \033[32m[4]\033[0m" << " Prodotto di polinomi -> P(1) * P(2)                                      " << "\033[36m|\n";
        cout << "\033[36m" << "|  \033[32m[5]\033[0m" << " Ricerca e visualizzazione degli zeri -> P(x) = 0                         " << "\033[36m|\n";
        cout << "\033[36m" << "|  \033[32m[6]\033[0m" << " Ricerca e visualizzazione dei punti di intersezione                      " << "\033[36m|\n";
        cout << "\033[36m" << "|  \033[32m[7]\033[0m" << " Rappresentazione grafica dei polinomi                                    " << "\033[36m|\n";
        cout << "\033[36m" << "|  \033[32m[8]\033[0m" << " Esci dal programma                                                       " << "\033[36m|\n";
        cout << "\033[36m" << "---------------------------------------------------------------------------------\033[0m\n\n";

        cout << "\033[1m Scegli un opzione \033[36m\n>>\033[0m ";
        option = getch();

        switch(option) {
            case '1': {
                system("cls");
                cout << "\033[36m" << "---------------------------------------------------------------------------------" << "\033[0m\n";
                cout << "\033[36m|"<< "\033[1m                           ACQUISIZIONE DEI POLINOMI                           " << "\033[1m|\033[0m\n";
                cout << "\033[36m" << "---------------------------------------------------------------------------------" << "\033[0m\n\n";

                // Riassegnamento dei valori di defualt
                for (int i = 0; i < MAX1; i++) {
                    polynomial1[i] = 0;
                    polynomial2[i] = 0;
                }

                // Controllo input del grado massimo del primo polinomio
                do {
                    cout << "\033[3mInserisci il grado massimo del primo polinomio:       \033[0m";
                    cin >> maxDegree1;

                    if (cin.fail())
                        cout << "\033[31mAttenzione! Il programma non accetta caratteri o altro, ma solo NUMERI! Riprova!\033[0m\n";
                    else if (maxDegree1 > 3 || maxDegree1 < 0)
                        cout << "\033[31mIl grado massimo del polinomio deve essere compreso tra 0 e 3, riprova!\033[0m\n";

                } while (inputChecking(maxDegree1));

                // Gestione input del primo polinomio
                for (int i = maxDegree1; i >= 0; i--) {
                    if (i != 0) {
                        do {
                            cout << "\033[3m\nInserisci il coefficiente di grado x^" << i << ":       \033[0m";
                            cin >> polynomial1[i];

                            if (cin.fail())
                                cout << "\033[31mAttenzione! Il programma non accetta caratteri o altro, ma solo NUMERI! Riprova!\033[0m\n";
                        } while (inputChecking(0));
                    } else {
                        do {
                            cout << "\033[3m\nInserisci il termine noto:       \033[0m";
                            cin >> polynomial1[i];

                            if (cin.fail()) {
                                cout << "\033[31mAttenzione! Il programma non accetta caratteri o altro, ma solo NUMERI! Riprova!\033[0m\n";
                            } 
                        } while (inputChecking(0));
                    }
                }

                // Gestione output del primo polinomio
                cout << "\n\n\033[32mP(1): \033[0m";
                printPoli(polynomial1, maxDegree1);
                cout << "\n\n";

                // Controllo input del grado massimo del secondo polinomio
                do {
                    cout << "\n\033[3mInserisci il grado massimo del secondo polinomio:       \033[0m";
                    cin >> maxDegree2;
                    
                    if (cin.fail())
                        cout << "\033[31mAttenzione! Il programma non accetta caratteri o altro, ma solo NUMERI! Riprova!\033[0m\n";
                    else if (maxDegree2 > 3 || maxDegree2 < 0)
                        cout << "\033[31mIl grado massimo del polinomio deve essere compreso tra 0 e 3, riprova!\033[0m\n";
                        
                } while (inputChecking(maxDegree2));
                
                // Gestione input del secondo polinomio
                for (int i = maxDegree2; i >= 0; i--) {
                    if (i > 0) {
                        do {
                            cout << "\n\033[3mInserisci il coefficiente di grado x^" << i << ":       \033[0m";
                            cin >> polynomial2[i];

                            if (cin.fail())
                                cout << "\033[31mAttenzione! Il programma non accetta caratteri o altro, ma solo NUMERI! Riprova!\033[0m\n";
                            
                        } while (inputChecking(0));
                    } else {
                        do {
                            cout << "\n\033[3mInserisci il termine noto:       \033[0m";
                            cin >> polynomial2[i];

                            if (cin.fail())
                                cout << "\033[31mAttenzione! Il programma non accetta caratteri o altro, ma solo NUMERI! Riprova!\033[0m\n";
                            
                        } while (inputChecking(0));
                    }
                }
                
                // Gestione output del primo polinomio
                cout << "\n\n\033[32mP(2): \033[0m";
                printPoli(polynomial2, maxDegree2);

                cout << "\n\n\033[4mPremere qualsiasi tasto per continuare...\033[0m";
                getch();
                system("cls");
                break;
            }
            case '2': {
                system("cls");
                cout << "\033[36m" << "---------------------------------------------------------------------------------" << "\033[0m\n";
                cout << "\033[36m|"<< "\033[1m                              SOMMA DI POLINOMI                                " << "\033[1m|\033[0m\n";
                cout << "\033[36m" << "---------------------------------------------------------------------------------" << "\033[0m\n\n";

                sum(polynomial1, polynomial2, sumPolynomial);

                // Gestione output del polinomio somma
                cout << "\033[32mLa somma tra i due polinomi equivale a: \033[0m\n\n";

                cout << "(";
                printPoli(polynomial1, maxDegree1);
                cout << ") + (";
                printPoli(polynomial2, maxDegree2);
                cout << ") = ";
                printPoli(sumPolynomial, maxDegree1 > maxDegree2 ? maxDegree1 : maxDegree2);

                cout << "\n\n\033[4mPremere qualsiasi tasto per continuare...\033[0m";
                getch();
                system("cls");
                break;
            }
            case '3': {
                system("cls");
                cout << "\033[36m" << "---------------------------------------------------------------------------------" << "\033[0m\n";
                cout << "\033[36m|"<< "\033[1m                           DIFFERENZA DI POLINOMI                              " << "\033[1m|\033[0m\n";
                cout << "\033[36m" << "---------------------------------------------------------------------------------" << "\033[0m\n\n";

                subtr(polynomial1, polynomial2, subtrPolynomial);

                // Gestione output del polinomio differenza
                cout << "\033[32mLa differenza tra i due polinomi equivale a: \033[0m\n\n";

                cout << "(";
                printPoli(polynomial1, maxDegree1);
                cout << ") - (";
                printPoli(polynomial2, maxDegree2);
                cout << ") = ";
                printPoli(subtrPolynomial, maxDegree1 > maxDegree2 ? maxDegree1 : maxDegree2);

                cout << "\n\n\033[4mPremere qualsiasi tasto per continuare...\033[0m";
                getch();
                system("cls");
                break;
            }
            case '4': {
                system("cls");
                cout << "\033[36m" << "---------------------------------------------------------------------------------" << "\033[0m\n";
                cout << "\033[36m|"<< "\033[1m                            PRODOTTO DI POLINOMI                               " << "\033[1m|\033[0m\n";
                cout << "\033[36m" << "---------------------------------------------------------------------------------" << "\033[0m\n\n";

                multi(polynomial1, polynomial2, multiPolynomial);

                // Gestione output del polinomio differenza
                cout << "\033[32mIl prodotto tra i due polinomi equivale a: \033[0m\n\n";

                cout << "(";
                printPoli(polynomial1, maxDegree1);
                cout << ") * (";
                printPoli(polynomial2, maxDegree2);
                cout << ") = ";
                printPoli(multiPolynomial, maxDegree1 + maxDegree2);

                cout << "\n\n\033[4mPremere qualsiasi tasto per continuare...\033[0m";
                getch();
                system("cls");
                break;
            }
            case '5': {
                system("cls");
                cout << "\033[36m" << "---------------------------------------------------------------------------------" << "\033[0m\n";
                cout << "\033[36m|"<< "\033[1m                     RICERCA E VISUALIZZAZIONE DEGLI ZERI                      " << "\033[1m|\033[0m\n";
                cout << "\033[36m" << "---------------------------------------------------------------------------------" << "\033[0m\n\n";
                
                cout << "\033[32mQuesti sono i polinomi che hai inserito: \033[0m\n\n";

                cout << "P(1) = ";
                printPoli(polynomial1, maxDegree1);

                cout << "  P(2) = ";
                printPoli(polynomial2, maxDegree2);

                cout << "\n\n\033[32mLe soluzione/i del P(1): \033[0m\n";

                if (polynomial1[MAX1 - 1] == 0) {
                    if (polynomial1[MAX1 - 2] != 0) 
                        quadraticFormula(polynomial1[MAX1 - 2], polynomial1[MAX1 - 3], polynomial1[0]);
                    else 
                        firstDegreeEquation(polynomial1[0], polynomial1[MAX1 - 3]);
                }

                cout << "\n\n\033[32mLe soluzione/i del P(2): \033[0m\n";

                if (polynomial2[MAX1 - 1] == 0) {
                    if (polynomial2[MAX1 - 2] != 0) 
                        quadraticFormula(polynomial2[MAX1 - 2], polynomial2[MAX1 - 3], polynomial2[0]);
                    else 
                        firstDegreeEquation(polynomial2[0], polynomial2[MAX1 - 3]);
                }

                cout << "\n\n\033[4mPremere qualsiasi tasto per continuare...\033[0m";
                getch();
                system("cls");
                break;
            }
            case '6': {
                system("cls");
                cout << "\033[36m" << "---------------------------------------------------------------------------------" << "\033[0m\n";
                cout << "\033[36m|"<< "\033[1m              RICERCA E VISUALIZZAZIONE DEI PUNTI DI INTERSEZIONE              " << "\033[1m|\033[0m\n";
                cout << "\033[36m" << "---------------------------------------------------------------------------------" << "\033[0m\n\n";

                subtr(polynomial1, polynomial2, subtrPolynomial);

                cout << "\033[32mQuesti sono i polinomi che sono stati inseriti dall'utente: \033[0m\n\n";

                cout << "P(1) = ";
                printPoli(polynomial1, maxDegree1);

                cout << "  P(2) = ";
                printPoli(polynomial2, maxDegree2);

                cout << "\n\n\033[32mIl punto di intersezione dei seguenti polinomi: \033[0m\n\n";

                if (subtrPolynomial[MAX1 - 1] == 0 && polynomial1[MAX1 - 1] == 0 && polynomial2[MAX1 - 1] == 0) {
                    if (subtrPolynomial[MAX1 - 2] != 0)
                        pointOfIntersectionForSecond(polynomial1, subtrPolynomial, false);
                    else {
                        pointOfIntersectionForFirst(polynomial1, polynomial2, subtrPolynomial, false);
                    }
                        
                } else {
                    cout << "\033[31mNon possibile trovare il punto di intersezione! Motivo: presenza di un polinomio di terzo grado!\033[0m";
                }

                cout << "\n\n\033[4mPremere qualsiasi tasto per continuare...\033[0m";
                getch();
                system("cls");
                break;
            }
            case '7': {
                system("cls");
	            cout << "\033[36m" << "---------------------------------------------------------------------------------" << "\033[0m\n";
	            cout << "\033[36m|"<< "\033[1m                            RAPPRESENTAZIONE GRAFICA                           " << "\033[1m|\033[0m\n";
	            cout << "\033[36m" << "---------------------------------------------------------------------------------" << "\033[0m\n\n";
        		
        		cout << "\033[31mSe si vuole chiudere la finestra del grafico premere un qualsiasi tasto.\033[0m\n";
        		cout << "\033[31mAlcuni polinomi non saranno ben rappresentati. Motivo: alcuni di essi crescescono di valore molto rapidamente.\033[0m\n";
        		cout << "\033[31mIl punto di intersezione tra i due polinomi verra' indicata con un cerchio di colore ciano.\033[0m\n";
        		cout << "\033[31mL'unita' scelta' (1:33)\033[0m\n\n";

                subtr(polynomial1, polynomial2, subtrPolynomial);

                cout << "\033[1mSicuro di voler continuare? (\033[32my\033[0m, \033[31mN\033[0m): \033[0m";
        		cin >> userChoice;
        		
        		if (tolower(userChoice) != 'y') {
        			system("cls");
        			continue;
				}

                initgraph(&graphDriver, &graphMode, "", WIDTH, HEIGHT);

                setcolor(DARKGRAY); // imposta il colore degli assi a bianco
            	line(WIDTH / 2, 0, WIDTH / 2, HEIGHT); // Asse delle ordinate
            	line(0, HEIGHT / 2, WIDTH, HEIGHT / 2); // Asse delle ascisse

                // Genera delle linee nell'asse delle ascisse 
            	setcolor(WHITE); // Imposta il colore delle lineette a magenta
            	for (int i = 33; i < WIDTH / 2; i += 33) {
            		line(WIDTH / 2 + i, HEIGHT / 2 - 8, WIDTH / 2 + i, HEIGHT / 2 + 8);
            		line(WIDTH / 2 - i, HEIGHT / 2 - 8, WIDTH / 2 - i, HEIGHT / 2 + 8);
				}
				
				// Genera delle linee nell'asse delle ordinate 
            	for (int i = 33; i < HEIGHT / 2; i += 33) {
                    line(WIDTH / 2 - 8, HEIGHT / 2 + i, WIDTH / 2 + 8, HEIGHT / 2 + i);
                    line(WIDTH / 2 - 8, HEIGHT / 2 - i, WIDTH / 2 + 8, HEIGHT / 2 - i);
				}

                // Inserisci i caratteri y e x all'interno del grafico
                outtextxy(WIDTH / 2 + 20, 10, "y");
                outtextxy(WIDTH - 30, HEIGHT / 2 + 20, "x");

                // Rappresentazione del punto di intersezione 
                setcolor(CYAN);

                if (subtrPolynomial[MAX1 - 1] == 0 && polynomial1[MAX1 - 1] == 0 && polynomial2[MAX1 - 1] == 0) {
                    if (subtrPolynomial[MAX1 - 2] != 0)
                        pointOfIntersectionForSecond(polynomial1, subtrPolynomial, true);
                    else 
                        pointOfIntersectionForFirst(polynomial1, polynomial2, subtrPolynomial, true);
                } else {
                    cout << "\033[31mNon possibile trovare il punto di intersezione! Motivo: presenza di un polinomio di terzo grado!\033[0m";
                }

                // Rappresentazione grafica del primo polinomio
            	setcolor(GREEN); // Imposta il colore del primo polinomio a verde
                graphicRapr(polynomial1);

                // Rappresentazione grafica del secondo polinomio
            	setcolor(YELLOW); // Imposta il colore del secondo polinomio a giallo
                graphicRapr(polynomial2);

                // Creazione della stringa contenente il primo polinomio
                setcolor(GREEN);
                outtextxy(10, 600, printPoliGraphic(polynomial1, maxDegree1).c_str());

                // Creazione della stringa contenente il secondo polinomio
                setcolor(YELLOW);
                outtextxy(10, 620, printPoliGraphic(polynomial2, maxDegree2).c_str());

                ShowWindow(GetConsoleWindow(), SW_HIDE);
            	getchg();
            	ShowWindow(GetConsoleWindow(), SW_SHOW);
            	closegraph();
            	system("cls");
            	break;
            }
            case '8': {
                system("cls");
            	cout << "Sei sicuro di voler uscire? (\033[32my\033[0m, \033[31mN\033[0m): ";
            	userExit = getch();
            	
            	if (tolower(userExit) != 'n') {
            		system("cls");
	                cout << "\033[36m" << "---------------------------------------------------------------------------------" << "\033[0m\n";
	                cout << "\033[36m|"<< "\033[1m                GRAZIE PER AVER PROVATO IL NOSTRO PROGRAMMA!                   " << "\033[1m|\033[0m\n";
	                cout << "\033[36m" << "---------------------------------------------------------------------------------" << "\033[0m\n\n";
	                
	                isRunning = false;
				} else {
					system("cls");
				}
                break;
            }
            default: {
                system("cls");
                cout << "\033[31mL'opzione inserita non e' disponibile. Riprovare per favore!\033[0m\n";
                break;
            }
        }
    }

    system("pause");
    return 0;
}