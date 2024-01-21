#include<iostream>
#include<fstream>
#include<string>
#include <stdlib.h>

using namespace std;

class head
{
    char Iname[100][100];
    char category[100][100];

public:
    int total_no_items;
    float quantity[3];
    float price[3];
    int total_fee[3];
    int tax[3];

    void input();
    void output();
    bool isValidCategory(const string& cat);
};

class vat : public head
{
    float vats;

public:
    void vatcal();
    void outputs();
    void sum();
};

//******************************************************************
// INPUT FUNCTION
//******************************************************************

void head::input()
{
    system("CLS");
    cout << "\n\t\t\t+---------------WELCOME TO CAFE77----------------+";
    cout << "\n\nEnter number of items do you want to buy: ";
    cin >> total_no_items;

    for (int i = 0; i < total_no_items; i++)
    {
        cout << "\nPlease enter name of item " << i + 1 << ": ";
        cin >> Iname[i];

        // Prompt user to enter a valid category
        do {
            cout << "Please enter category of item " << i + 1 << " (food, beverages, desserts): ";
            cin >> category[i];
            if (!isValidCategory(category[i]))
            {
                cout << "Error: Invalid category. Please enter a valid category (food, beverages, desserts).\n";
            }
        } while (!isValidCategory(category[i]));

        cout << "Please enter quantity: ";
        cin >> quantity[i];
        cout << "Please enter price of the item " << i + 1 << ": ";
        cin >> price[i];
        total_fee[i] = quantity[i] * price[i];
    }
}

// Validate if the entered category is valid
bool head::isValidCategory(const string& cat)
{
    // Valid categories: food, beverages, desserts
    return cat == "food" || cat == "beverages" || cat == "desserts";
}

//******************************************************************
// OUTPUT FUNCTION
//******************************************************************

void head::output()
{
    int y;

    ifstream infile("BILLNO.TXT");
    infile >> y;

    ofstream outfile("BILLNO.TXT");
    y += 1;
    outfile << y;
    outfile.close();

    {
        ofstream outfile("INVOICE.TXT", ios::app);
        outfile << endl
                << "Bill No.: " << y << endl;
        outfile << "+------------------------------------------------------------------------+" << endl;
        cout << "\n";
        cout << "Name of Item\tCategory\t  Quantity   Price    Total Price\n";
        for (int i = 0; i < total_no_items; i++)
        {
            outfile << "Name: " << Iname[i] << " Category: " << category[i] << " Qty: " << quantity[i] << " Price: " << total_fee[i] << endl;
            cout << Iname[i] << "\t\t" << category[i] << "\t\t " << quantity[i] << "\t   " << price[i] << "\t   " << total_fee[i] << '\n';
        }

        outfile << "+------------------------------------------------------------------------+" << endl;
        outfile.close();
    }
}

//******************************************************************
// VAT CALCULATION
//******************************************************************

void vat::vatcal()
{
    input();
    for (int i = 0; i < total_no_items; i++)
    {
        if (price[i] <= 100.00)
        {
            tax[i] = total_fee[i] + (0.03 * total_fee[i]);
        }
        else
        {
            // Apply discounts based on total amount
            float totalAmount = total_fee[i];
            if (totalAmount >= 5000 && totalAmount < 10000)
            {
                tax[i] = totalAmount - (0.001 * totalAmount);
            }
            else if (totalAmount >= 10000 && totalAmount < 25000)
            {
                tax[i] = totalAmount - (0.002 * totalAmount);
            }
            else if (totalAmount >= 25000)
            {
                tax[i] = totalAmount - (0.005 * totalAmount);
            }
            else
            {
                // No discount
                tax[i] = totalAmount;
            }
        }
    }
}

//******************************************************************
// VAT OUTPUTS
//******************************************************************

void vat::outputs()
{
    output();

    float cash = 0, sum = 0, qty = 0, sumt = 0;

    for (int i = 0; i < total_no_items; i++)
    {
        sumt += total_fee[i];
        sum += tax[i];
        qty += quantity[i];
    }
    cout << "\nTotal Summary:";
    cout << "\n------------------------------------------------------------------------------";
    cout << "\n\tQuantity= " << qty << "\t\t Total Price " << sumt << "\tWith tax Total Price:" << sum;
    cout << "\n------------------------------------------------------------------------------";

pay:

    cout << "\n\n\t\t\t****PAYMENT INVOICE****\n";
    cout << "\n\t\t\tTotal cash given: ";
    cin >> cash;

    if (cash >= sum)
        cout << "\n\t\t\tTotal cash balance: " << cash - sum << '\n';

    else
    {
        cout << "\n\t\t\tPlease give valid cash. Given is less than the total amount!!!";

        goto pay;
    }
}

//******************************************************************
// PROTECTION PASSWORD
//******************************************************************

int authenticateUser()
{
    std::string username, password;

    std::cout << "\n\n\n\n\n\n\t\t\tEnter your username: ";
    std::cin >> username;

    std::cout << "\t\t\tEnter your password: ";
    std::cin >> password;

    // Check if the entered username and password are correct
    if (username == "sahan" && password == "sahan")
    {
        std::cout << "\n\t\t\tLogin successful!\n\n";
        return 1;
    }
    else
    {
        std::cout << "\n\t\t\tLogin failed. Invalid Username or Password.!!\n\n";
        return 0;
    }
}
// END of Password.

//****************************************************************
// THE MAIN FUNCTION OF PROGRAM
//******************************************************************

int main()
{
    vat obj;
    char option, ch;
    int a = 1;
    ifstream fin;

    a = authenticateUser();
    if (!a)
    {
        for (int i = 0; i < 2; i++)
        {
            cout << "\n Invalid attempt, try once more\n";
            if (authenticateUser())
            {
                goto last;
            }
            else
            {
                cout << "\n\n\t\t\tAll Login attempts failed.....";
                cout << "\n\n\n\t\t\tSee you again later.................. ";
                exit(0);
            }
        }
        cout << "\t\t\tSorry, all attempts failed. Please try again later............. \n \t\t\tInactive";
    }
    else
    {
    last:

        do
        {
        start:
            system("PAUSE");
            system("CLS");
            cout << "\n\n\t\t\t----------------------------------";
            cout << "\n\t\t\t\tWELCOME TO CAFE77";
            cout << "\n\t\t\t Billing Management System Cafe77";
            cout << "\n\t\t\t----------------------------------";
            cout << "\n\n\t\t\tWhat do you need?";
            cout << "\n\t\t\t1.\tTo enter a new record\n\t\t\t2.\tTo view previous records\n\t\t\t3.\tExit\n";
            cout << "\n\nPlease enter your option: ";
            cin >> option;
            switch (option)
            {
            case '1':
                obj.vatcal();
                obj.outputs();
                goto start;
            case '2':
                fin.open("INVOICE.TXT", ios::in);
                while (fin.get(ch))
                {
                    cout << ch;
                }
                fin.close();
                goto start;
            case '3':
                exit(0);
            default:
                cout << "\a";
            }
        } while (option != '3');
    }
    return 0;
}
