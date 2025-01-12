#include "calculator.h"
#include "./ui_calculator.h"   //generirani UI kod (od strane Qt Designer-a) koji definira elemente korisničkog sučelja (UI)
#include <stack>   // implementacija evaluacije izraza koristeći stog za operatore i vrijednosti.
#include <cctype>

double calcVal = 0.0;

//konstruktor klase Calculator
Calculator::Calculator(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Calculator)
{
    ui->setupUi(this);  //Inicijalizira sve elemente korisničkog sučelja
    ui->Display->setText(QString::number(calcVal));  //postavlja pocetnu vrijednost kalkulatora na nulu

    QPushButton *numButtons[10];  //polje za pohranjivanje referenci na gumbove s brojevima

    for(int i = 0; i < 10; i++){
        QString butName = "Button" + QString::number(i);
        numButtons[i] = Calculator::findChild<QPushButton *>(butName);

        connect(numButtons[i], SIGNAL(released()), this, SLOT(NumPressed()));   //Povezuje svaki brojčani gumb sa signalom released i slotom NumPressed()
    }

    connect(ui->Add, SIGNAL(released()), this, SLOT(MathButtonPressed()));
    connect(ui->Subtract, SIGNAL(released()), this, SLOT(MathButtonPressed()));
    connect(ui->Multiply, SIGNAL(released()), this, SLOT(MathButtonPressed()));
    connect(ui->Divide, SIGNAL(released()), this, SLOT(MathButtonPressed()));
    connect(ui->Equals, SIGNAL(released()), this, SLOT(EqualButtonPressed()));
    connect(ui->Clear, SIGNAL(released()), this, SLOT(ClearPressed()));
    connect(ui->ChangeSign, SIGNAL(released()), this, SLOT(ChangeNumberSign()));
    connect(ui->BrackLeft, SIGNAL(released()), this, SLOT(BrackLeftPressed()));
    connect(ui->BrackRight, SIGNAL(released()), this, SLOT(BrackRightPressed()));
    connect(ui->Point, SIGNAL(released()), this, SLOT(PointPressed()));
}

Calculator::~Calculator()
{
    delete ui;
}

// pomocna funkcija za definiranje prvenstva operatora kod racunanja
int precedence(char op) {
    if(op == '+' || op == '-') return 1;
    if(op == '*' || op == '/') return 2;
    return 0;
}

// fnkcija za izvedbu matem operacija
double applyOp(double a, double b, char op) {
    switch(op) {
    case '+': return a + b;
    case '-': return a - b;
    case '*': return a * b;
    case '/': return a / b;
    }
    return 0;
}

// funkcija evaluacije izraza, rad s tockom i zagradama
double evaluateExpression(const std::string& tokens) {
    std::stack<double> values;
    std::stack<char> ops;
    bool lastWasOperator = true;  // Za rukovanje negativnim brojevima

    for(size_t i = 0; i < tokens.length(); i++) {
        if (tokens[i] == ' ') {
            continue;  // Ignoriraj praznine
        }

        if(isdigit(tokens[i]) || tokens[i] == '.') {
            double val = 0;
            double fraction = 0.0;
            bool isFraction = false;
            double fractionDivisor = 10;

            while(i < tokens.length() && (isdigit(tokens[i]) || tokens[i] == '.')) {
                if (tokens[i] == '.') {
                    if (isFraction) {
                        // Višestruke točke nisu dopuštene
                        throw std::invalid_argument("Invalid number format");
                    }
                    isFraction = true;
                } else {
                    if (isFraction) {
                        fraction += (tokens[i] - '0') / fractionDivisor;
                        fractionDivisor *= 10;
                    } else {
                        val = (val * 10) + (tokens[i] - '0');
                    }
                }
                i++;
            }

            val += fraction;
            values.push(val);
            lastWasOperator = false;  // Sljedeći znak ne bi trebao biti minus kao unary operator
            i--;  // Korigiraj zbog vanjske petlje
        } else if(tokens[i] == '(') {
            ops.push(tokens[i]);
            lastWasOperator = true;  // Nakon '(' može biti unary minus
        } else if(tokens[i] == ')') {
            while(!ops.empty() && ops.top() != '(') {
                double val2 = values.top(); values.pop();
                double val1 = values.top(); values.pop();
                char op = ops.top(); ops.pop();
                values.push(applyOp(val1, val2, op));
            }
            ops.pop();  // Ukloni '('
        } else if(tokens[i] == '+' || tokens[i] == '-' || tokens[i] == '*' || tokens[i] == '/') {
            if (tokens[i] == '-' && lastWasOperator) {
                // Unary minus detektiran, nastavite parsirati broj kao negativan
                values.push(0);  // Dodaj nulu prije unarnog minusa za ispravnu evaluaciju
            }

            while(!ops.empty() && precedence(ops.top()) >= precedence(tokens[i])) {
                double val2 = values.top(); values.pop();
                double val1 = values.top(); values.pop();
                char op = ops.top(); ops.pop();
                values.push(applyOp(val1, val2, op));
            }
            ops.push(tokens[i]);
            lastWasOperator = true;  // Nakon operatora može doći još jedan operator (unary)
        }
    }

    while(!ops.empty()) {
        double val2 = values.top(); values.pop();
        double val1 = values.top(); values.pop();
        char op = ops.top(); ops.pop();
        values.push(applyOp(val1, val2, op));
    }

    return values.top();
}

//Dodaje broj ili decimalnu točku na trenutni prikaz
void Calculator::NumPressed() {
    QPushButton *button = (QPushButton *)sender();
    QString butVal = button->text();
    QString displayVal = ui->Display->text();

    if ((displayVal == "0") && (butVal != ".")) {
        ui->Display->setText(butVal);
    } else {
        ui->Display->setText(displayVal + butVal);
    }
}

//dodavanje matematickog operatora
void Calculator::MathButtonPressed() {
    QPushButton *button = (QPushButton *)sender();
    QString butVal = button->text();
    QString displayVal = ui->Display->text();
    ui->Display->setText(displayVal + butVal);
}

void Calculator::EqualButtonPressed() {
    QString displayVal = ui->Display->text();
    double result = evaluateExpression(displayVal.toStdString());
    ui->Display->setText(QString::number(result, 'g', 16)); // ispis rijesenja do 16 znamenki
}

void Calculator::ClearPressed() {
    ui->Display->setText("0");
}

void Calculator::ChangeNumberSign() {
    QString displayVal = ui->Display->text();
    double dblDisplayVal = displayVal.toDouble();
    dblDisplayVal = -dblDisplayVal;
    ui->Display->setText(QString::number(dblDisplayVal));
}

void Calculator::BrackLeftPressed() {
    QPushButton *button = (QPushButton *)sender();
    QString butVal = button->text();
    QString displayVal = ui->Display->text();
    if (displayVal == "0") {
        ui->Display->setText(butVal);
    } else {
        ui->Display->setText(displayVal + butVal);
    }
}

void Calculator::BrackRightPressed() {
    QPushButton *button = (QPushButton *)sender();
    QString butVal = button->text();
    QString displayVal = ui->Display->text();
    ui->Display->setText(displayVal + butVal);
}

void Calculator::PointPressed() {
    QString displayVal = ui->Display->text();
    if (!displayVal.contains('.')) {
        ui->Display->setText(displayVal + ".");
    }
}
