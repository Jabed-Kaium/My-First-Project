#include<iostream>
#include<stdio.h>
#include<string.h>
#include<fstream>
#include<iomanip>
#include<string>
using namespace std;

class Apartment
{
protected:
    int id;
    bool rent[12];
    bool charges[12];
public:
    void createFlat();
    void display();
    int return_ID();
    int return_rent(int m);
    int return_charges(int m);
    void rentBill(int m);
    void chargesBill(int m);
};

class Owner : public Apartment
{
    char name[50];
    char contact[20];
    char address[100];
    public:
    char* return_Name();
    char* return_Contact();
    char* return_Address();
    void createOwner();
    void setID(int n);
};

void Apartment::rentBill(int m)
{
    rent[m] = 1;
}

void Apartment::chargesBill(int m)
{
    charges[m] = 1;
}

int Apartment::return_ID()
{
    return id;
}
int Apartment::return_rent(int m)
{
    return rent[m];
}
int Apartment::return_charges(int m)
{
    return charges[m];
}
char* Owner::return_Name()
{
    return name;
}

char* Owner::return_Contact()
{
    return contact;
}

char* Owner::return_Address()
{
    return address;
}

void Owner::setID(int n)
{
    id = n;
}

void Owner::createOwner()
{
    cout << "\nEnter Flat Owner Name : \n";
    cin>>name;
    cout << "\nEnter Contact No. : \n";
    cin>>contact;
    cout << "\nEnter Address : \n";
    cin>>address;
}

void Apartment::createFlat()
{
    cout << "\nEnter Flat no : \n";
    cin>>id;
    for(int i=0; i<12; i++)
    {
        rent[i] = 0;
        charges[i] = 0;
    }
}

void Apartment::display()
{
    cout << "Month                Rent        Charges\n\n";
    cout << "January" << setw(18) << (rent[0]==0 ? "N/A" : "Paid") << setw(15) << (charges[0]==0 ? "N/A" : "Paid") << "\n";
    cout << "February" << setw(17) << (rent[1]==0 ? "N/A" : "Paid") << setw(15) << (charges[1]==0 ? "N/A" : "Paid") << "\n";
    cout << "March" << setw(20) << (rent[2]==0 ? "N/A" : "Paid") << setw(15) << (charges[2]==0 ? "N/A" : "Paid") << "\n";
    cout << "April" << setw(20) << (rent[3]==0 ? "N/A" : "Paid") << setw(15) << (charges[3]==0 ? "N/A" : "Paid") << "\n";
    cout << "May" << setw(22) << (rent[4]==0 ? "N/A" : "Paid") << setw(15) << (charges[4]==0 ? "N/A" : "Paid") << "\n";
    cout << "June" << setw(21) << (rent[5]==0 ? "N/A" : "Paid") << setw(15) << (charges[5]==0 ? "N/A" : "Paid") << "\n";
    cout << "July" << setw(21) << (rent[6]==0 ? "N/A" : "Paid") << setw(15) << (charges[6]==0 ? "N/A" : "Paid") << "\n";
    cout << "August" << setw(19) << (rent[7]==0 ? "N/A" : "Paid") << setw(15) << (charges[7]==0 ? "N/A" : "Paid") << "\n";
    cout << "September" << setw(16) << (rent[8]==0 ? "N/A" : "Paid") << setw(15) << (charges[8]==0 ? "N/A" : "Paid") << "\n";
    cout << "October" << setw(18) << (rent[9]==0 ? "N/A" : "Paid") << setw(15) << (charges[9]==0 ? "N/A" : "Paid") << "\n";
    cout << "November" << setw(17) << (rent[10]==0 ? "N/A" : "Paid") << setw(15) << (charges[10]==0 ? "N/A" : "Paid") << "\n";
    cout << "December" << setw(17) << (rent[11]==0 ? "N/A" : "Paid") << setw(15) << (charges[11]==0 ? "N/A" : "Paid") << "\n";
}

fstream file , file2;
Apartment pr;
Owner ob;

void design()
{
    cout << "\n--------------------------------------------------------------------------------------------\n";
}

void addFlat()
{
    system("cls");
    file.open("Flats.dat",ios::in);
    file2.open("Owners.dat",ios::out|ios::app);

    if(!file)
    {
        file.open("Flats.dat",ios::out);

        pr.createFlat();
        ob.createOwner();
        ob.setID(pr.return_ID());

        file.write((char*)&pr,sizeof(Apartment));
        file2.write((char*)&ob,sizeof(Owner));

        file.close();
        cout << "\nSuccessfully Added.\n\n";
        system("pause");

        return;
    }

    fstream f1,f2,f3;
    Apartment tmp;
    f1.open("First.dat",ios::out);
    f2.open("Last.dat",ios::out);
    f3.open("Temporary.dat",ios::out);

    pr.createFlat();
    ob.createOwner();
    ob.setID(pr.return_ID());

    //file.write((char*)&pr,sizeof(Apartment));
    file2.write((char*)&ob,sizeof(Owner));

    file.read((char*)&tmp,sizeof(Apartment));
    while(!file.eof())
    {
        if(tmp.return_ID() < pr.return_ID())
        {
            f1.write((char*)&tmp,sizeof(Apartment));
        }
        else if(tmp.return_ID() > pr.return_ID())
        {
            f2.write((char*)&tmp,sizeof(Apartment));
        }
        file.read((char*)&tmp,sizeof(Apartment));
    }

    file.close();
    file2.close();
    f1.close();
    f2.close();

    f1.open("First.dat",ios::in);
    f2.open("Last.dat",ios::in);

    f1.read((char*)&tmp,sizeof(Apartment));
    while(!f1.eof())
    {
        f3.write((char*)&tmp,sizeof(Apartment));
        f1.read((char*)&tmp,sizeof(Apartment));
    }
    f3.write((char*)&pr,sizeof(Apartment));
    f2.read((char*)&tmp,sizeof(Apartment));
    while(!f2.eof())
    {
        f3.write((char*)&tmp,sizeof(Apartment));
        f2.read((char*)&tmp,sizeof(Apartment));
    }

    f1.close();
    f2.close();
    f3.close();

    remove("Flats.dat");
    rename("Temporary.dat","Flats.dat");

    cout << "\nSuccesfully Added.\n\n";

    system("pause");
}

void deleteFlat()
{
    system("cls");
    int n , flag = 0;
    fstream f1,f2;
    f1.open("tempFlat.dat",ios::out);
    f2.open("tempOwner.dat",ios::out);
    file.open("Flats.dat",ios::in);
    file2.open("Owners.dat",ios::in);

    if(!file)
    {
        cout << "\nCan't Open File!\n\n";
        system("pause");
        return;
    }

    cout << "\nEnter Flat No. you want to delete : \n";
    cin>>n;
    file.read((char*)&pr,sizeof(Apartment));
    while(!file.eof())
    {
        if(pr.return_ID() != n)
        {
            f1.write((char*)&pr,sizeof(Apartment));
        }
        else if(pr.return_ID() == n)
        {
            flag = 1;
        }
        file.read((char*)&pr,sizeof(Apartment));
    }
    file.close();
    f1.close();
    
    file2.read((char*)&ob,sizeof(Owner));
    while(!file2.eof())
    {
        if(ob.return_ID() != n)
        {
            f2.write((char*)&ob,sizeof(Owner));
        }
        file2.read((char*)&ob,sizeof(Owner));
    }
    file2.close();
    f2.close();

    remove("Flats.dat");
    remove("Owners.dat");
    rename("tempFlat.dat","Flats.dat");
    rename("tempOwner.dat","Owners.dat");

    if(flag == 0)
    {
        cout << "\nFlat Not Found!\n\n";
    }
    else
    {
        cout << "\nSuccessfully Deleted.\n\n";
    }
    

    system("pause");
}

void showAll()
{
    system("cls");
    int flag = 0;
    file.open("Flats.dat",ios::in);
    if(!file)
    {
        cout << "\nCan't Open File!\n\n";
        system("pause");
        return;
    }
    else
    {
        file.read((char*)&pr,sizeof(Apartment));
        while(!file.eof())
        {
            file2.open("Owners.dat",ios::in);
            design();
            cout << "\nFlat No : " << pr.return_ID() << "\n";
            file2.read((char*)&ob,sizeof(Owner));
            while(!file2.eof())
            {
                if(ob.return_ID() == pr.return_ID())
                {
                    cout << "Holders Name : " << ob.return_Name() << "\n";
                    flag = 1;
                    break;
                }
                file2.read((char*)&ob,sizeof(Owner));
            }
            file2.close();
            cout << "\n";
            pr.display();

            file.read((char*)&pr,sizeof(Apartment));
        }
        file.close();
        if(flag == 1)
        {
            design();
        }
        cout << "\n";
        system("pause");
    }
    
}

void showSpecific()
{
    system("cls");
    int n , flag = 0;
    cout << "Enter Flat No. : \n";
    cin>>n;
    file.open("Flats.dat",ios::in);
    if(!file)
    {
        cout << "\nCan't Open File!\n\n";
        system("pause");
        return;
    }
    else
    {
        file.read((char*)&pr,sizeof(Apartment));
        while(!file.eof() && flag == 0)
        {
            if(pr.return_ID() == n)
            {
                system("cls");
                design();
                cout << "\nFlat No : " << pr.return_ID() << "\n";
                file2.open("Owners.dat",ios::in);
                file2.read((char*)&ob,sizeof(Owner));
                while(!file2.eof())
                {
                    if(ob.return_ID() == pr.return_ID())
                    {
                        cout << "Holders Name : " << ob.return_Name() << "\n";
                        break;
                    }
                    file2.read((char*)&ob,sizeof(Owner));
                }
                file2.close();
                cout << "\n";
                pr.display();
                design();
                flag = 1;
            }
            file.read((char*)&pr,sizeof(Apartment));
        }

        file.close();
        if(flag == 0)
        {
            cout << "\nFlat details not found!\n\n";
        }
        cout << "\n";
        system("pause");
    }
    
}

void showOwner()
{
    system("cls");
    file.open("Flats.dat",ios::in);
    if(!file)
    {
        cout << "\nCan't Open File!\n\n";
        system("pause");
        return;
    }
    design();
    cout << "\nFlat No.          Owner Name          Contact          Address\n\n";
    file.read((char*)&pr,sizeof(Apartment));
    while(!file.eof())
    {
        int flag = 0;
        file2.open("Owners.dat",ios::in);
        file2.read((char*)&ob,sizeof(Owner));
        while(!file2.eof() && flag == 0)
        {
            if(pr.return_ID() == ob.return_ID())
            {
                cout << pr.return_ID() << setw(27) << ob.return_Name() << setw(17) << ob.return_Contact() << "          " << ob.return_Address() << "\n";
                flag = 1;
            }
            file2.read((char*)&ob,sizeof(Owner));
        }
        file2.close();
        file.read((char*)&pr,sizeof(Apartment));
    }
    file.close();
    design();
    cout << "\n";
    system("pause");
}

void payRent()
{
    system("cls");
    file.open("Flats.dat",ios::in|ios::out);
    if(!file)
    {
        cout << "\nCan't Open File!\n\n";
        system("pause");
        return;
    }
    int n , amount, flag = 0, flag2 = 0;
    char mon[20];
    cout << "\nEnter Your Flat No. : \n";
    cin>>n;
    file.read((char*)&pr,sizeof(Apartment));
    while(!file.eof() && flag == 0)
    {
        if(pr.return_ID() == n)
        {
            cout << "\nEnter Month You Want To Pay (i.e. January) : \n";
            cin>>mon;
            if(strcmp(mon,"JANUARY") == 0 || strcmp(mon,"January") == 0 || strcmp(mon,"january") == 0)
            {
                do
                {
                    cout << "\nEnter Amount (15000) : \n";
                    cin>>amount;
                    if(amount != 15000)
                    {
                        cout << "\nSorry amount doesn't match! Please enter exactly 15000.\n";
                    }
                } while (amount != 15000);
                
                pr.rentBill(0);
                flag2 = 1;
            }
            else if(strcmp(mon,"FEBRUARY") == 0 || strcmp(mon,"February") == 0 || strcmp(mon,"february") == 0)
            {
                do
                {
                    cout << "\nEnter Amount (15000) : \n";
                    cin>>amount;
                    if(amount != 15000)
                    {
                        cout << "\nSorry amount doesn't match! Please enter exactly 15000.\n";
                    }
                } while (amount != 15000);

                pr.rentBill(1);
                flag2 = 1;
            }
            else if(strcmp(mon,"MARCH") == 0 || strcmp(mon,"March") == 0 || strcmp(mon,"march") == 0)
            {
                do
                {
                    cout << "\nEnter Amount (15000) : \n";
                    cin>>amount;
                    if(amount != 15000)
                    {
                        cout << "\nSorry amount doesn't match! Please enter exactly 15000.\n";
                    }
                } while (amount != 15000);

                pr.rentBill(2);
                flag2 = 1;
            }
            else if(strcmp(mon,"APRIL") == 0 || strcmp(mon,"April") == 0 || strcmp(mon,"april") == 0)
            {
                do
                {
                    cout << "\nEnter Amount (15000) : \n";
                    cin>>amount;
                    if(amount != 15000)
                    {
                        cout << "\nSorry amount doesn't match! Please enter exactly 15000.\n";
                    }
                } while (amount != 15000);

                pr.rentBill(3);
                flag2 = 1;
            }
            else if(strcmp(mon,"MAY") == 0 || strcmp(mon,"May") == 0 || strcmp(mon,"may") == 0)
            {
                do
                {
                    cout << "\nEnter Amount (15000) : \n";
                    cin>>amount;
                    if(amount != 15000)
                    {
                        cout << "\nSorry amount doesn't match! Please enter exactly 15000.\n";
                    }
                } while (amount != 15000);

                pr.rentBill(4);
                flag2 = 1;
            }
            else if(strcmp(mon,"JUNE") == 0 || strcmp(mon,"June") == 0 || strcmp(mon,"june") == 0)
            {
                do
                {
                    cout << "\nEnter Amount (15000) : \n";
                    cin>>amount;
                    if(amount != 15000)
                    {
                        cout << "\nSorry amount doesn't match! Please enter exactly 15000.\n";
                    }
                } while (amount != 15000);

                pr.rentBill(5);
                flag2 = 1;
            }
            else if(strcmp(mon,"JULY") == 0 || strcmp(mon,"July") == 0 || strcmp(mon,"july") == 0)
            {
                do
                {
                    cout << "\nEnter Amount (15000) : \n";
                    cin>>amount;
                    if(amount != 15000)
                    {
                        cout << "\nSorry amount doesn't match! Please enter exactly 15000.\n";
                    }
                } while (amount != 15000);

                pr.rentBill(6);
                flag2 = 1;
            }
            else if(strcmp(mon,"AUGUST") == 0 || strcmp(mon,"August") == 0 || strcmp(mon,"august") == 0)
            {
                do
                {
                    cout << "\nEnter Amount (15000) : \n";
                    cin>>amount;
                    if(amount != 15000)
                    {
                        cout << "\nSorry amount doesn't match! Please enter exactly 15000.\n";
                    }
                } while (amount != 15000);

                pr.rentBill(7);
                flag2 = 1;
            }
            else if(strcmp(mon,"SEPTEMBER") == 0 || strcmp(mon,"September") == 0 || strcmp(mon,"september") == 0)
            {
                do
                {
                    cout << "\nEnter Amount (15000) : \n";
                    cin>>amount;
                    if(amount != 15000)
                    {
                        cout << "\nSorry amount doesn't match! Please enter exactly 15000.\n";
                    }
                } while (amount != 15000);

                pr.rentBill(8);
                flag2 = 1;
            }
            else if(strcmp(mon,"OCTOBER") == 0 || strcmp(mon,"October") == 0 || strcmp(mon,"october") == 0)
            {
                do
                {
                    cout << "\nEnter Amount (15000) : \n";
                    cin>>amount;
                    if(amount != 15000)
                    {
                        cout << "\nSorry amount doesn't match! Please enter exactly 15000.\n";
                    }
                } while (amount != 15000);

                pr.rentBill(9);
                flag2 = 1;
            }
            else if(strcmp(mon,"NOVEMBER") == 0 || strcmp(mon,"November") == 0 || strcmp(mon,"november") == 0)
            {
                do
                {
                    cout << "\nEnter Amount (15000) : \n";
                    cin>>amount;
                    if(amount != 15000)
                    {
                        cout << "\nSorry amount doesn't match! Please enter exactly 15000.\n";
                    }
                } while (amount != 15000);

                pr.rentBill(10);
                flag2 = 1;
            }
            else if(strcmp(mon,"DECEMBER") == 0 || strcmp(mon,"December") == 0 || strcmp(mon,"december") == 0)
            {
                do
                {
                    cout << "\nEnter Amount (15000) : \n";
                    cin>>amount;
                    if(amount != 15000)
                    {
                        cout << "\nSorry amount doesn't match! Please enter exactly 15000.\n";
                    }
                } while (amount != 15000);

                pr.rentBill(11);
                flag2 = 1;
            }
            else
            {
                cout << "\nIncorrect Month! Please Try Again.\n\n";
            }

            int pos = (-1)*sizeof(Apartment);
            file.seekp(pos,ios::cur);
            file.write((char*)&pr,sizeof(Apartment));

            flag = 1;
        }
        file.read((char*)&pr,sizeof(Apartment));
    }

    file.close();

    if(flag == 0)
    {
        cout << "\nFlat Not Found!\n\n";
    }
    if(flag2 == 1)
    {
        cout << "\nSuccessfully Paid.\n\n";
    }

    system("pause");
}

void payCharges()
{
    system("cls");
    file.open("Flats.dat",ios::in|ios::out);
    if(!file)
    {
        cout << "\nCan't Open File!\n\n";
        system("pause");
        return;
    }
    int n , amount, flag = 0, flag2 = 0;
    char mon[20];
    cout << "\nEnter Your Flat No. : \n";
    cin>>n;
    file.read((char*)&pr,sizeof(Apartment));
    while(!file.eof() && flag == 0)
    {
        if(pr.return_ID() == n)
        {
            cout << "\nEnter Month You Want To Pay (i.e. January) : \n";
            cin>>mon;
            if(strcmp(mon,"JANUARY") == 0 || strcmp(mon,"January") == 0 || strcmp(mon,"january") == 0)
            {
                do
                {
                    cout << "\nEnter Amount (2000) : \n";
                    cin>>amount;
                    if(amount != 2000)
                    {
                        cout << "\nSorry amount doesn't match! Please enter exactly 2000.\n";
                    }
                } while (amount != 2000);

                pr.chargesBill(0);
                flag2 = 1;
            }
            else if(strcmp(mon,"FEBRUARY") == 0|| strcmp(mon,"February") == 0|| strcmp(mon,"february") == 0)
            {
                do
                {
                    cout << "\nEnter Amount (2000) : \n";
                    cin>>amount;
                    if(amount != 2000)
                    {
                        cout << "\nSorry amount doesn't match! Please enter exactly 2000.\n";
                    }
                } while (amount != 2000);

                pr.chargesBill(1);
                flag2 = 1;
            }
            else if(strcmp(mon,"MARCH") == 0 || strcmp(mon,"March") == 0 || strcmp(mon,"march") == 0)
            {
                do
                {
                    cout << "\nEnter Amount (2000) : \n";
                    cin>>amount;
                    if(amount != 2000)
                    {
                        cout << "\nSorry amount doesn't match! Please enter exactly 2000.\n";
                    }
                } while (amount != 2000);

                pr.chargesBill(2);
                flag2 = 1;
            }
            else if(strcmp(mon,"APRIL") == 0 || strcmp(mon,"April") == 0 || strcmp(mon,"april") == 0)
            {
                do
                {
                    cout << "\nEnter Amount (2000) : \n";
                    cin>>amount;
                    if(amount != 2000)
                    {
                        cout << "\nSorry amount doesn't match! Please enter exactly 2000.\n";
                    }
                } while (amount != 2000);

                pr.chargesBill(3);
                flag2 = 1;
            }
            else if(strcmp(mon,"MAY") == 0 || strcmp(mon,"May") == 0 || strcmp(mon,"may") == 0)
            {
                do
                {
                    cout << "\nEnter Amount (2000) : \n";
                    cin>>amount;
                    if(amount != 2000)
                    {
                        cout << "\nSorry amount doesn't match! Please enter exactly 2000.\n";
                    }
                } while (amount != 2000);

                pr.chargesBill(4);
                flag2 = 1;
            }
            else if(strcmp(mon,"JUNE") == 0 || strcmp(mon,"June") == 0 || strcmp(mon,"june") == 0)
            {
                do
                {
                    cout << "\nEnter Amount (2000) : \n";
                    cin>>amount;
                    if(amount != 2000)
                    {
                        cout << "\nSorry amount doesn't match! Please enter exactly 2000.\n";
                    }
                } while (amount != 2000);

                pr.chargesBill(5);
                flag2 = 1;
            }
            else if(strcmp(mon,"JULY") == 0 || strcmp(mon,"July") == 0 || strcmp(mon,"july") == 0)
            {
                do
                {
                    cout << "\nEnter Amount (2000) : \n";
                    cin>>amount;
                    if(amount != 2000)
                    {
                        cout << "\nSorry amount doesn't match! Please enter exactly 2000.\n";
                    }
                } while (amount != 2000);

                pr.chargesBill(6);
                flag2 = 1;
            }
            else if(strcmp(mon,"AUGUST") == 0 || strcmp(mon,"August") == 0 || strcmp(mon,"august") == 0)
            {
                do
                {
                    cout << "\nEnter Amount (2000) : \n";
                    cin>>amount;
                    if(amount != 2000)
                    {
                        cout << "\nSorry amount doesn't match! Please enter exactly 2000.\n";
                    }
                } while (amount != 2000);

                pr.chargesBill(7);
                flag2 = 1;
            }
            else if(strcmp(mon,"SEPTEMBER") == 0 || strcmp(mon,"September") == 0 || strcmp(mon,"september") == 0)
            {
                do
                {
                    cout << "\nEnter Amount (2000) : \n";
                    cin>>amount;
                    if(amount != 2000)
                    {
                        cout << "\nSorry amount doesn't match! Please enter exactly 2000.\n";
                    }
                } while (amount != 2000);

                pr.chargesBill(8);
                flag2 = 1;
            }
            else if(strcmp(mon,"OCTOBER") == 0 || strcmp(mon,"October") == 0 || strcmp(mon,"october") == 0)
            {
                do
                {
                    cout << "\nEnter Amount (2000) : \n";
                    cin>>amount;
                    if(amount != 2000)
                    {
                        cout << "\nSorry amount doesn't match! Please enter exactly 2000.\n";
                    }
                } while (amount != 2000);

                pr.chargesBill(9);
                flag2 = 1;
            }
            else if(strcmp(mon,"NOVEMBER") == 0 || strcmp(mon,"November") == 0 || strcmp(mon,"november") == 0)
            {
                do
                {
                    cout << "\nEnter Amount (2000) : \n";
                    cin>>amount;
                    if(amount != 2000)
                    {
                        cout << "\nSorry amount doesn't match! Please enter exactly 2000.\n";
                    }
                } while (amount != 2000);

                pr.chargesBill(10);
                flag2 = 1;
            }
            else if(strcmp(mon,"DECEMBER") == 0 || strcmp(mon,"December") == 0 || strcmp(mon,"december") == 0)
            {
                do
                {
                    cout << "\nEnter Amount (2000) : \n";
                    cin>>amount;
                    if(amount != 2000)
                    {
                        cout << "\nSorry amount doesn't match! Please enter exactly 2000.\n";
                    }
                } while (amount != 2000);
                
                pr.chargesBill(11);
                flag2 = 1;
            }
            else
            {
                cout << "\nIncorrect Month!Please Try Again.\n\n";
            }

            int pos = (-1)*sizeof(Apartment);
            file.seekp(pos,ios::cur);
            file.write((char*)&pr,sizeof(Apartment));

            flag = 1;
        }
        file.read((char*)&pr,sizeof(Apartment));
    }

    file.close();

    if(flag == 0)
    {
        cout << "\nFlat Not Found!\n\n";
    }
    if(flag2 == 1)
    {
        cout << "\nSuccessfully Paid.\n\n";
    }

    system("pause");
}

void renter()
{
    system("cls");
    int n;

    cout << "\n1.Pay Rent\n";
    cout << "2.Pay Charges\n";
    cout << "3.My Details\n";
    cout << "4.Exit\n";
    cin>>n;
    switch(n)
    {
        case 1:
                payRent();
                break;
        case 2:
                payCharges();
                break;
        case 3:
                showSpecific();
                break;
        case 4:
                return;
        default:
                cout << "\a";
    }
}

void admin()
{
    system("cls");
    int n;
    cout << "\n1.Add Flat Info\n";
    cout << "2.Delete Flat Info\n";
    cout << "3.Show All Flat Details\n";
    cout << "4.Show Specific Flat Details\n";
    cout << "5.Owners List\n";
    cout << "6.Exit\n";
    cin>>n;
    switch(n)
    {
        case 1:
                addFlat();
                break;
        case 2:
                deleteFlat();
                break;
        case 3:
                showAll();
                break;
        case 4:
                showSpecific();
                break;
        case 5:
                showOwner();
                break;
        case 6:
                return;
        default:
                cout << "\a";
    }
}

void intro()
{
    system("cls");
    cout << "\n\n\t\tApartment Management System\n";
    cout << "\n\t\tPrepared by : Jabed Kaium\n";
    cout << "\n\t\t14 Batch\n";
    cout << "\n\t\tDepartment Of Computer Science and Telecommunication Engineering\n";
    cout << "\n\t\tNoakhali Science and Technology University\n\n";

    system("pause");
}

int main()
{
    intro();

    int n;
    do
    {   system("cls");
        cout << "\nMAIN MENU\n\n";
        cout << "1.Administration\n";
        cout << "2.Flat Holder\n";
        cout << "3.Exit\n";
        cin>>n;
        switch (n)
        {
        case 1:
                admin();
                break;
        case 2:
                renter();
                break;
        case 3:
                exit(0);

        default:
                cout << "\a";
                break;
        }
    } while (n != 3);
    

    return 0;
}