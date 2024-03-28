#pragma once

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class Shopping
{
    public:
        int productCode;
        float price;
        float discount;
        string productName;

    public:
        void menu() {
            int choice;
            string email;
            string password;

            cout << "\t\t\t\t___________________________\n";
            cout << "\t\t\t\t                           \n";
            cout << "\t\t\t\t   Supermarket Main Menu   \n";
            cout << "\t\t\t\t                           \n";
            cout << "\t\t\t\t___________________________\n";
            cout << "\t\t\t\t|  1) Administrator  |\n";
            cout << "\t\t\t\t|                    |\n";
            cout << "\t\t\t\t|  2) Buyer          |\n";
            cout << "\t\t\t\t|                    |\n";
            cout << "\t\t\t\t|  3) Exit           |\n";
            cout << "\t\t\t\t|                    |\n";
            cout << "\n\t\t Please enter your choice: ";
            cin >> choice;

            switch (choice)
            {
                case 1:
                    cout << "\t\t\t Pleasee Login \n";
                    cout << "\t\t\t Enter Email:   \n";
                    cin >> email;
                    cout << "\t\t\t Password:      \n";
                    cin >> password;

                    administrator();
                    break;
                case 2:
                    buyer();
                    break;
                case 3:
                    exit(0);
                    break;
                default:
                    cout << "Please select from the given option";
            }
        }

        void administrator() {
            int choice;
            cout << "\n\n\n\t\t\t Administrator menu";
            cout << "\n\t\t\t|_____1) Add the product____|";
            cout << "\n\t\t\t|                           |";
            cout << "\n\t\t\t|_____2) Modify the product_|";
            cout << "\n\t\t\t|                           |";
            cout << "\n\t\t\t|_____3) Delete the product_|";
            cout << "\n\t\t\t|                           |";
            cout << "\n\t\t\t|_____4) Back to main menu__|";
            cout << "\n\t\t\t Please enter your choice: ";
            cin >> choice;

            switch (choice)
            {
                case 1:
                    add();
                    break;
                case 2:
                    edit();
                    break;
                case 3:
                    removeProduct();
                    break;
                case 4:
                    menu();
                    break;
                default:
                    cout << "Please select from the given option";
            }
        }

        void buyer() {
            int choice;
            cout << "\t\t\t Buyer  \n";
            cout << "\t\t\t_______________\n";
            cout << "                     \n";
            cout << "\t\t\t1) Buy product \n";
            cout << "                     \n";
            cout << "\t\t\t2) Go back     \n";
            cout << "\t\t\t Please enter your choice: ";
            cin >> choice;

            switch (choice)
            {
                case 1:
                    receipt();
                    break;
                case 2:
                    menu();
                    break;
                default:
                    cout << "Please select from the given option";
            }
        }

        void add() {
            fstream data;
            int c;
            int token = 0;
            float p;
            float d;
            string n;

            cout << "\n\n\t\t\t Add new product";
            cout << "\n\n\t Product code of the product: ";
            cin >> productCode;
            cout << "\n\n\t Name of the product: ";
            cin >> productName;
            cout << "\n\n\t Price of the product: ";
            cin >> price;
            cout << "\n\n\t Discount on product: ";
            cin >> discount;

            data.open("database.txt", ios::in);

            if (!data)
            {
                data.open("database.txt", ios::app | ios::out);
                data << " " << productCode << " " << productName << " " << price << " " << discount << "\n";
                data.close();
            }
            else
            {
                data >> c >> n >> p >> d;

                while (!data.eof())
                {
                    if (c == productCode)
                    {
                        token++;
                    }
                    data >> c >> n >> p >> d;
                }

                if (token == 1)
                {
                    data.close();
                    menu();
                }
                else
                {
                    data.open("database.txt", ios::app | ios::out);
                    data << " " << productCode << " " << productName << " " << price << " " << discount << "\n";
                    data.close();
                }
            }
            cout << "\n\n\t Record inserted!";
            administrator();
        }

        void edit() {
            fstream data, data1;
            int pkey;
            int token = 0;
            int c;
            float p;
            float d;
            string n;

            cout << "\n\t\t\t Modify the record";
            cout << "\n\t\t\t Product code: ";
            cin >> pkey;

            data.open("database.txt", ios::in);
            if (!data)
            {
                cout << "\n\n File doesn't exist! ";
            }
            else
            {
                data1.open("database.txt", ios::app | ios::out);

                data >> productCode >> productName >> price >> discount;
                while (!data.eof())
                {
                    if (pkey == productCode)
                    {
                        cout << "\n\t\t Product new code :";
                        cin >> c;
                        cout << "\n\t\t Name of the product :";
                        cin >> n;
                        cout << "\n\t\t Price :";
                        cin >> p;
                        cout << "\n\t\t Discount :";
                        cin >> d;
                        data1 << " " << c << " " << n << " " << p << " " << d << "\n";
                        cout << "\n\n\t\t Record edited ";
                        token++;
                    }
                    else
                    {
                        data1 << " " << productCode << " " << productName << " " << price << " " << discount << " " << "\n";
                    }
                    data >> productCode >> productName >> price >> discount;
                }
                data.close();
                data1.close();

                remove("database.txt");
                rename("database1.txt", "database.txt");

                if (token == 0)
                {
                    cout << "\n\n Record not found sorry!";
                }
            }
            administrator();
        }

        void removeProduct() {
            fstream data, data1;
            int pkey;
            int token = 0;
            cout << "\n\n\t Delete product";
            cout << "\n\n\t Product code: ";
            cin >> pkey;
            data.open("database.txt", ios::in);
            if (!data)
            {
                cout << "File doesn't exist";
            }
            else
            {
                data1.open("database1.txt", ios::app | ios::out);
                data >> productCode >> productName >> price >> discount;
                while (!data.eof())
                {
                    if (productCode == pkey)
                    {
                        cout << "\n\n\t Product deleted successfully";
                        token++;
                    }
                    else
                    {
                        data1 << " " << productCode << " " << productName << " " << price << " " << discount << "\n";
                    }
                    data >> productCode >> productName >> price >> discount;
                }
                data.close();
                data1.close();

                remove("database.txt");
                rename("database1.txt", "database.txt");

                if (token == 0)
                {
                    cout << "\n\n Record not found";
                }
            }
            administrator();
        }

        void list() {
            fstream data;
            data.open("database.txt", ios::in);
            cout << "\n\n|__________________________________\n";
            cout << "ProNo\t\tName\t\tPrice\n";
            cout << "\n\n|____________________________________\n";
            data >> productCode >> productName >> price >> discount;
            while (!data.eof())
            {
                cout << productCode << "\t\t" << productName << "\t\t" << price << "/n";
            }
            data.close();
        }

        void receipt() {

            fstream data;
            int arrc[100];
            int arrq[100];
            char choice;
            int c = 0;
            float amount = 0;
            float dis = 0;
            float total = 0;

            cout << "\n\n\t\t\t\t RECEIPT ";
            data.open("database.txt", ios::in);
            if (!data)
            {
                cout << "\n\n Empty database";
            }
            else
            {
                data.close();

                list();
                cout << "\n______________________________/n";
                cout << "\n|                             \n";
                cout << "\n    Please place the order    \n";
                cout << "\n|                             \n";
                cout << "\n______________________________/n";

                do
                {
                    cout << "\n\n Enter product code: ";
                    cin >> arrc[c];
                    cout << "\n\n Enter the product quantity: ";
                    cin >> arrq[c];
                    for (int i = 0; i < c; i++)
                    {
                        if (arrc[c] == arrc[i])
                        {
                            cout << "\n\n Duplicate product code. Pleasee try again!";
                        }
                    }
                    c++;
                    cout << "\n\n Do you want to buy another product? if yes then press y else no";
                    cin >> choice;
                } while (choice == 'y');

                cout << "\n\n\t\t\t_____________RECEIPT_______________\n";
                cout << "\nProduct No\t Product Name\t Product quantity\t price\t Amount with discount\n";

                for (int i = 0; i < c; i++)
                {
                    data.open("database.txt", ios::in);
                    data >> productCode >> productName >> price >> dis;
                    while (!data.eof())
                    {
                        if (productCode == arrc[i])
                        {
                            amount = price * arrq[i];
                            dis = amount - (amount * dis / 100);
                            total = total + dis;
                            cout << "\n" << productCode << "\t\t" << productName << "\t\t" << arrq[i] << "\t\t" << price << "\t" << amount << "\t\t" << dis;
                        }
                        data >> productCode >> productName >> price >> dis;
                    }
                }
                data.close();
            }
            cout << "\n\n___________________________________________";
            cout << "\n Total Amount : " << total;
        }
};

