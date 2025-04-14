# include<iostream>
# include<stdlib.h>
# include<unistd.h>
# include<time.h>
# include<conio.h>
# include<string.h>
# include<math.h>
# include<fstream>
# include<stack>
using namespace std;
string name;
double funds;
double profit;
    void details()
    {
        cout<<"Enter your name: ";
        getline(cin,name);
        cout<<"Enter your funds: ";
        cin>>funds;
        if(funds<0)
            funds=0;

        cout<<"________________________________________________"<<endl<<endl;
    }
    void add_funds()
    {
        double f1;
        cout<<"Enter the amount you want to add: ";
        cin>>f1;
        if(f1>=0)
            {
                funds+=f1;
                profit=profit+f1;
                cout<<"Funds added"<<endl;
            }
        else
            {
                cout<<"Can't add "<<f1<<" funds"<<endl;
                add_funds();
            }

    }
    void withdraw_funds()
    {
        double f1;
        cout<<"Enter the amount you want to withdraw: ";
        cin>>f1;
        if(funds>=f1&&f1>=0)
            {
                funds-=f1;
                profit=profit-f1;
                cout<<"Withdrawal successful"<<endl;
            }
        else
            {
                cout<<"Can't withdraw "<<f1<<" funds"<<endl;
                withdraw_funds();
            }
    }
void print_account()
{

    cout<<"**************************************"<<endl;int x;
    cout<<"Name: "<<name<<endl;
    cout<<"Funds: "<<funds<<endl;
    cout<<"Overall Profit: "<<funds-profit<<endl;
    cout<<"**************************************"<<endl;
    ifstream obj;
    obj.open("demat.txt");
    string str;
    while(!obj.eof())
    {
        getline(obj,str);
        if(!obj.eof())
            cout<<str<<endl;
    }
    cout<<"**************************************"<<endl;
    cout<<"Enter any digit to return: ";
    cin>>x;
    profit=funds;
}
    void choice()
    {
        int x;
        cout<<endl<<"Enter your choice:"<<endl<<"1) Add funds"<<endl<<"2) Withdraw funds"<<endl<<"3) Print details"<<endl<<"0) exit"<<endl;
        cin>>x;
        switch(x)
        {
        case 1:
            add_funds();
            choice();
            break;
        case 2:
            withdraw_funds();
            choice();
            break;
        case 3:
            print_account();
            choice();
            break;
        case 0:
            break;
        default:
            cout<<"Wrong choice enter again."<<endl;
            choice();
        }
    }
double pricing(double price)
{
            int rand1=rand()%5;
            if(rand1==0)
                {
                    price=price*1.002;
                }
            else if(rand1==1)
                {
                    price=price*0.998;
                }
            else if(rand1==2)
                {
                    price=price*0.999;
                }
            else if(rand1==3)
                {
                    price=price*1.001;
                }
                return price;
}
class order
{
public:
    int serial;
    string name;
    //int quantity;
    double price;
   // static double funds;
    order()
    {
        serial=0;
        name="";
        //quantity=0;
        price=0.0;
        //funds=0.0;
    }
    /*order(int x,string str,double p)
    {
        serial=x;
        name=str;
        //quantity=q;
        price=p;
        //funds=funds1;
    }*/
    order(int x,string str,double p)
    {
        serial=x;
        name=str;
        //quantity=q;
        price=p;
    }
    double order_choice()
    {
        int x;int y;int quantity;
        cout<<"1) Buy"<<endl<<"2) Sell"<<endl;
        cin>>x;
        cout<<"Enter quantity: ";
        cin>>quantity;
        if(x==1)
        {
            cout<<"1) Market order(buy at market value)"<<endl<<"2) Limit order(buy at your own price.)"<<endl<<"3) Stoploss order(reduce your risk)"<<endl<<"4) Stoploss limit order(buy at your price with reducing risk)"<<endl;
            cin>>y;

            if(quantity>0)
            {switch(y)
            {
            case 1:
                buy_market(quantity);
                break;
            case 2:
                price=buy_limit(quantity);
                break;
            case 3:
                price=buy_stoploss(quantity);
                break;
            case 4:
                price=buy_stoploss_limit(quantity);
                break;
            default:
                cout<<"Wrong choice enter again.";
                order_choice();
                break;
            }}
            else
            {
                cout<<"Wrong choice.";
                order_choice();
            }
        }
        else if(x==2)
        {
            int count1=0;string word;int s;int c=0;
            string str;
            ifstream obj1;
            obj1.open("demat.txt");
            /*while(!obj1.eof())
            {
                getline(obj1,str);
                if(!obj1.eof())
                    cout<<str<<endl;
            }
            cout<<"************************************************";
            cout<<"Enter serial number";
            cin>>m;
            obj1.seekg(0,ios::beg);*/
            getline(obj1,str);
            while(!obj1.eof())
            {
                obj1>>word;
                s=stoi(word);
                count1++;
                if(s==serial)
                    {c++;break;}
                    getline(obj1,str);
            }
            if(c==0)
                cout<<"You don't have any stocks"<<endl;
            if(c==1)
            {
                int y;
                cout<<endl<<"1) Market order(sell at market price)"<<endl<<"2) Limit order(choose your own price to sell)"<<endl;
                cin>>y;
                switch(y)
                {
                case 1:
                    sell_market(quantity);
                    break;
                case 2:
                    sell_limit(quantity);
                    break;
                default:
                    cout<<"Wrong choice.Enter again";
                    order_choice();
                    break;
                }
            }
        }
        else
            cout<<"Wrong choice";
        return price;
    }
    void buy_market(int quantity)
    {

        int x;
        if(quantity*price<=funds)
        {
            ofstream obj;
            obj.open("order_class.txt",ios::app);
            obj<<serial<<"\t"<<name<<"\t"<<quantity<<"\t"<<price<<"\t"<<"buy"<<"\t"<<"Executed"<<endl;
            funds=funds-quantity*price;
            //profit=profit-quantity*price;
            ofstream obj1;
            obj1.open("demat.txt",ios::app);
            obj1<<serial<<"    "<<name<<"    "<<quantity<<endl;


            /*string str,word;int count3=0,count4=0;
            char a[100],b[100];int s1,s2;string str2;
            ifstream o1;
            o1.open("demat.txt");
            if(o1.eof())
            {
                ofstream o3;
                o3.open("demat.txt",ios::app);
                o3<<serial<<"    "<<name<<"    "<<quantity<<endl;
                return ;
            }
            else
            {ofstream o2;
            o2.open("temporary_order.txt",ios::app);
            getline(o1,str);
            while(!o1.eof())
            {
                getline(o1,str);
                count3++;


                    for(int i=0;i<str.length();i++)
                        a[i]=str[i];
                    s1=stoi(a);
                    for(int i=5;i<name.length()+9;i++)
                        str2=str2+str[i];
                    for(int i=10+name.length();i<str.length();i++)
                        b[i]=str[i];
                    s2=stoi(b);
                    if(s1==serial);
                        {
                            count4++;
                            break;
                        }
                        s1=0;s2=0;str2="";
            }
            if(count4==0)
            {
                ofstream o3;
                o3.open("demat.txt",ios::app);
                o3<<serial<<"    "<<name<<"    "<<quantity<<endl;
                return ;
            }
            else if(count4==1)
            {
                count4=0;
                ifstream o4;
                o4.open("demat.txt");
                while(!o4.eof())
                {
                    getline(o4,str);
                    count4++;
                    for(int i=0;i<5;i++)
                        a[i]=str[i];
                    s1=stoi(a);
                    for(int i=5;i<name.length()+5;i++)
                        str2=str2+str[i];
                    for(int i=10+name.length();i<str.length();i++)
                        b[i]=str[i];
                    s2=stoi(b);
                    if(count4==count3)
                    {
                        s2=s2+quantity;
                        o2<<s1<<"    "<<name<<"    "<<s2<<endl;
                    }
                    else
                        o2<<s1<<"    "<<name<<"    "<<s2<<endl;
                }
            }}*/
        }
        else
        {
            ofstream obj;
            obj.open("order_class.txt",ios::app);
            obj<<serial<<"\t"<<name<<"\t"<<quantity<<"\t"<<price<<"\t"<<"buy"<<"\t"<<"Rejected."<<endl;
            cout<<"Not enough funds."<<endl;
            cout<<"1) Add more funds."<<endl<<"2) Back to watchlist"<<endl;
            cin>>x;
            if(x==1)
                add_funds();
            else if(x==2)
                return;
        }
    }
    void sell_market(int quantity)
    {
        ofstream obj;
            obj.open("order_class.txt",ios::app);
            obj<<serial<<"\t"<<name<<"\t"<<quantity<<"\t"<<price<<"\t"<<"sell"<<"\t"<<"Executed"<<endl;
            funds=funds+quantity*price;
            //profit=profit+quantity*price;
            ofstream obj1;
            obj1.open("demat.txt",ios::app);
            obj1<<serial<<"    "<<name<<"    -"<<quantity<<endl;

        /*int quantity;
        string str;
        cout<<"Enter the quantity to sell: ";
        cin>>quantity;
        ofstream obj3;
        obj3.open("order_class.txt",ios::app);
        ifstream obj1;
        obj1.open("demat.txt");
        ofstream obj2;
        obj2.open("temporary_order.txt");
        int count2=0;char a[100],b[100];int s1,s2;string str2;
        getline(obj1,str);
        if(str.length()!=0)
            obj1.seekg(0,ios::beg);
        while(!obj1.eof())
        {
            getline(obj1,str);
            count2++;
            if(!obj1.eof())
            {if(count1==count2)
            {
                for(int i=0;i<5;i++)
                    a[i]=str[i];
                s1=stoi(a);
                for(int i=5;i<name.length()+5;i++)
                    str2=str2+str[i];
                for(int i=10+name.length();i<str.length();i++)
                    b[i]=str[i];
                s2=stoi(b);

                if(quantity<=s2)
                {
                    s2=s2-quantity;
                    if(s2>0)
                    {
                        obj2<<s1<<"    "<<str2<<"    "<<s2<<endl;
                    }
                    obj3<<name<<"\t"<<quantity<<"\t"<<price<<"\t"<<"sell"<<"\t"<<"Executed"<<endl;
                    funds=funds+price*quantity;
                }
                else
                    {
                        obj2<<str<<endl;
                        obj3<<name<<"\t"<<quantity<<"\t"<<price<<"\t"<<"sell"<<"\t"<<"Rejected"<<endl;
                    }
            }
            else
                obj2<<str<<endl;
            }
        }
        ofstream obj4;
        obj4.open("demat.txt",ios::app);
        ifstream obj5;
        obj5.open("temporary_order.txt");
        while(!obj5.eof())
        {
            getline(obj5,str);
            if(!obj5.eof())
                obj4<<str<<endl;
        }*/





        /*string str="";string word;
        int s=0,s1=0;int i=0;
        char a[10],b[10];
        ifstream obj;
        obj.open("demat.txt");
        ofstream obj1;
        obj1.open("temporary_order.txt");



        getline(obj,str);
        if(str.length()!=0)
            obj.seekg(0,ios::beg);

        while(!obj.eof())
        {
            /*getline(obj,str);
            for(i=0;i<str.length();i++)
                a[i]=str[i];

            s=stoi(a);
            for(i=5;i<str.length();i++)
                    b[i-5]=str[i];

                s1=stoi(b);
                //if(!obj.eof())
                //cout<<s<<"    "<<s1<<endl;

            obj>>word;
            s=stoi(word);

            if(x==s)
            {
                    s1=s1-y;
            }
            if(!obj.eof())
            obj1<<s<<"    "<<s1<<endl;
            s=0;s1=0;
        }
        str="";
        ofstream obj3;
        obj3.open("demat.txt");
        ifstream obj2;
        obj2.open("temporary_order.txt");
        while(!obj2.eof())
        {
            getline(obj2,str);
            if(!obj2.eof())
            obj3<<str<<endl;
        }*/

    }

    /*void sell_limit1(int quantity)
    {
        int x;int count2=0;char a[100],b[100];int s1,s2;string str2;string str="";
        int quantity;
        cout<<"Enter the quantity you want to sell: ";
        cin>>quantity;
        double limit_price;
        cout<<"Set the limit price: ";
        cin>>limit_price;
        ofstream obj3;
        obj3.open("order_class.txt",ios::app);
        ifstream obj1;
        obj1.open("demat.txt");
        ofstream obj2;
        obj2.open("temporary_order.txt");
        getline(obj1,str);
        if(str.length()!=0)
            obj1.seekg(0,ios::beg);
        if(limit_price > price)
        {
            while(limit_price>price)
            {
                system("cls");
                cout<<name<<"    "<<quantity<<"    "<<limit_price<<"    "<<price<<"    "<<"buy"<<endl;
                cout<<"1) Cancel this order."<<endl<<"2) Back to watchlist"<<endl;
                price=pricing(price);
                sleep(1);
                if(kbhit())
                {
                    x=getch();
                    x=x-48;
                    switch(x)
                    {
                    case 1:
                        obj3<<name<<"\t"<<quantity<<"\t"<<limit_price<<"\t"<<"sell"<<"\t"<<"Cancelled"<<endl;
                        return;
                    case 2:
                        break;
                    default:
                        cout<<"Wrong choice"<<endl;

                    }
                }
            }
            system("cls");
            if(limit_price<=price)
            {
                while(!obj1.eof())
                {
                    getline(obj1,str);
                    count2++;
                    if(!obj1.eof())
                    {if(count1==count2)
                    {
                        for(int i=0;i<5;i++)
                            a[i]=str[i];
                        s1=stoi(a);
                        for(int i=5;i<name.length()+5;i++)
                            str2=str2+str[i];
                        for(int i=10+name.length();i<str.length();i++)
                            b[i]=str[i];
                        s2=stoi(b);

                        if(quantity<=s2)
                        {
                            s2=s2-quantity;
                            if(s2>0)
                            {
                                obj2<<s1<<"    "<<str2<<"    "<<s2<<endl;
                            }
                            obj3<<name<<"\t"<<quantity<<"\t"<<price<<"\t"<<"sell"<<"\t"<<"Executed"<<endl;
                            funds=funds+price*quantity;
                        }
                        else
                        {
                            obj2<<str<<endl;
                            obj3<<name<<"\t"<<quantity<<"\t"<<price<<"\t"<<"sell"<<"\t"<<"Rejected"<<endl;
                        }
                    }
                    else
                        obj2<<str<<endl;
                    }
                }
                    //obj3<<name<<"\t"<<quantity<<"\t"<<price<<"\t"<<"buy"<<"\t"<<"Executed"<<endl;
                    //obj1<<serial<<"    "<<name<<"    "<<quantity<<endl;
                    //funds=funds+quantity*price;
                }
            }
            else
            {
                obj3<<name<<"\t"<<quantity<<"\t"<<limit_price<<"\t"<<"sell"<<"\t"<<"Rejected."<<endl;
                return;
            }
        ofstream obj4;
        obj4.open("demat.txt",ios::app);
        ifstream obj5;
        obj5.open("temporary_order.txt");
        while(!obj5.eof())
        {
            getline(obj5,str);
            if(!obj5.eof())
                obj4<<str<<endl;
        }
    }*/
    void sell_limit(int quantity)
    {
       int x;
        double limit_price;
        cout<<"Enter the limit price: ";
        cin>>limit_price;
         ofstream obj2;
               obj2.open("order_class.txt",ios::app);
            ofstream obj1;
            obj1.open("demat.txt",ios::app);

        if(limit_price>price)
            {
                while(limit_price>price)
                {
                    system("cls");
                    cout<<serial<<"\t"<<name<<"    "<<quantity<<"    "<<limit_price<<"    "<<price<<"    "<<"sell"<<endl;
                    cout<<"*****************************************************************"<<endl;
                    cout<<"1) Cancel this order."<<endl<<"2) Back to watchlist (WARNING: you won't be able to access this order again)"<<endl;
                    cout<<"*****************************************************************"<<endl;
                    price=pricing(price);
                    sleep(1);
                    if(kbhit())
                {
                    x=getch();
                    if(x==49)
                    {
                        obj2<<serial<<"\t"<<name<<"\t"<<quantity<<"\t"<<limit_price<<"\t"<<"sell"<<"\t"<<"Cancelled"<<endl;
                        return;
                    }
                    else if(x==50)
                        {//obj1<<serial<<"    "<<name<<"   "quantity<<endl;
                        break;}
                    else
                        cout<<"Wrong choice."<<endl;
                }
                }
                system("cls");
                if(price<=limit_price)
                {

                    obj2<<serial<<"\t"<<name<<"\t"<<quantity<<"\t"<<price<<"\t"<<"sell"<<"\t"<<"Executed"<<endl;
                    obj1<<serial<<"    "<<name<<"    "<<quantity<<endl;
                    funds=funds+quantity*price;
                   // profit=profit+quantity*price;
                }
           }
           else
           {
               obj2<<serial<<"\t"<<name<<"\t"<<quantity<<"\t"<<limit_price<<"\t"<<"sell"<<"\t"<<"Rejected."<<endl;
               return;
           }
    }
    double buy_limit(int quantity)
    {
        int x;
        double limit_price;
        cout<<"Enter the limit price: ";
        cin>>limit_price;
        if(quantity*limit_price<=funds)
        {
            int x;
            //ofstream obj1;
            //obj1.open("order.txt",ios::app);
            ofstream obj2;
               obj2.open("order_class.txt",ios::app);
            ofstream obj1;
            obj1.open("demat.txt",ios::app);

            if(limit_price<price)
            {


                while(limit_price<price)
                {
                    system("cls");
                    cout<<serial<<"\t"<<name<<"    "<<quantity<<"    "<<limit_price<<"    "<<price<<"    "<<"buy"<<endl;
                    cout<<"*****************************************************************"<<endl;
                    cout<<"1) Cancel this order."<<endl<<"2) Back to watchlist (WARNING: you won't be able to access this order again)"<<endl;
                    cout<<"*****************************************************************"<<endl;
                    price=pricing(price);
                    sleep(1);
                    if(kbhit())
                {
                    x=getch();
                    if(x==49)
                    {
                        obj2<<serial<<"\t"<<name<<"\t"<<quantity<<"\t"<<limit_price<<"\t"<<"buy"<<"\t"<<"Cancelled"<<endl;
                        return price;
                    }
                    else if(x==50)
                        {//obj1<<serial<<"    "<<name<<"   "quantity<<endl;
                        break;}
                    else
                        cout<<"Wrong choice."<<endl;
                }
                }
                system("cls");
                if(price<=limit_price)
                {

                    obj2<<serial<<"\t"<<name<<"\t"<<quantity<<"\t"<<price<<"\t"<<"buy"<<"\t"<<"Executed"<<endl;
                    obj1<<serial<<"    "<<name<<"    "<<quantity<<endl;
                    funds=funds-quantity*price;
                   // profit=profit-quantity*price;
                }
           }
           else
           {
               obj2<<serial<<"\t"<<name<<"\t"<<quantity<<"\t"<<limit_price<<"\t"<<"buy"<<"\t"<<"Rejected."<<endl;
               return price;
           }

        }
        else
        {
            ofstream obj;
            obj.open("order_class.txt",ios::app);
            obj<<serial<<"\t"<<name<<"\t"<<quantity<<"\t"<<limit_price<<"\t"<<"buy"<<"\t"<<"Rejected."<<endl;
            cout<<"Not enough funds."<<endl;
            cout<<"1) Add more funds."<<endl<<"2) Back to watchlist"<<endl;
            cin>>x;
            if(x==1)
                add_funds();
            else if(x==2)
                return price;
        }
        return price;
    }
    double buy_stoploss(int quantity)
    {
        int x;
        double stop_loss_price;
        cout<<"Enter your stoploss price: ";
        cin>>stop_loss_price;
        if(quantity*price<=funds)
        {
            ofstream obj;
                obj.open("order_class.txt",ios::app);
            ofstream obj1;
                obj1.open("demat.txt",ios::app);
            if(stop_loss_price<price)
            {

                obj<<serial<<"\t"<<name<<"\t"<<quantity<<"\t"<<price<<"\t"<<"buy"<<"\t"<<"Executed"<<endl;
                obj1<<serial<<"    "<<name<<"    "<<quantity<<endl;
                funds=funds-quantity*price;
                //profit=profit-quantity*price;
                while(stop_loss_price<price)
                {
                    system("cls");
                    cout<<serial<<"\t"<<name<<"    "<<quantity<<"    "<<stop_loss_price<<"    "<<price<<"    "<<"sell"<<endl;
                    cout<<"*****************************************************************"<<endl;
                    cout<<"1) Cancel this order."<<endl<<"2) Back to watchlist (WARNING: you won't be able to access this order again)"<<endl;
                cout<<"*****************************************************************"<<endl;
                if(kbhit())
                {
                    x=getch();
                    if(x==49)
                    {
                        obj<<serial<<"\t"<<name<<"\t"<<quantity<<"\t"<<stop_loss_price<<"\t"<<"sell"<<"\t"<<"Cancelled"<<endl;

                        return price;
                    }
                    else if(x==50)
                        {//obj1<<serial<<"    "<<quantity<<endl;
                        break;}
                    else
                        cout<<"Wrong choice."<<endl;
                }
                    price=pricing(price);
                    sleep(1);
                }
                if(price<=stop_loss_price)
                {
                    obj<<serial<<"\t"<<name<<"\t"<<quantity<<"\t"<<price<<"\t"<<"sell"<<"\t"<<"Executed"<<endl;
                    obj1<<serial<<"    "<<name<<"    -"<<quantity<<endl;
                    funds=funds+quantity*price;
                    //profit=profit+quantity*price;
                }
            }
            else
            {
                obj<<serial<<"\t"<<name<<"\t"<<quantity<<"\t"<<price<<"\t"<<"Buy"<<"\t"<<"Rejected."<<endl;
                return price;
            }
                system("cls");


        }
        else
        {
            ofstream obj;
            obj.open("order_class.txt",ios::app);
            obj<<serial<<"\t"<<name<<"\t"<<quantity<<"\t"<<price<<"\t"<<"buy"<<"\t"<<"Rejected."<<endl;
            cout<<"Not enough funds."<<endl;
            cout<<"1) Add more funds."<<endl<<"2) Back to watchlist"<<endl;
            cin>>x;
            if(x==1)
                add_funds();
            else if(x==2)
                return price;
        }
        return price;
    }
    double buy_stoploss_limit(int quantity)
    {
        int x;
        double stop_loss_price,limit_order;
        cout<<"Enter the limit price: ";
        cin>>limit_order;
        cout<<"Enter the stop loss price: ";
        cin>>stop_loss_price;
        if(quantity*limit_order<=funds)
        {
            if(limit_order< price && stop_loss_price< limit_order)
            {
                ofstream obj;
                obj.open("order_class.txt",ios::app);
                ofstream obj1;
                obj1.open("demat.txt",ios::app);
                while(limit_order<price)
                {
                    system("cls");
                    cout<<serial<<"\t"<<name<<"    "<<quantity<<"    "<<limit_order<<"    "<<price<<"    "<<"buy"<<endl;
                    cout<<"*****************************************************************"<<endl;
                    cout<<"1) Cancel this order."<<endl<<"2) Back to watchlist (WARNING: you won't be able to access this order again)"<<endl;
                    cout<<"*****************************************************************"<<endl;
                price=pricing(price);
                    sleep(1);
                if(kbhit())
                {
                    x=getch();
                    cout<<x;
                    switch(x)
                    {
                    case 49:
                        obj<<serial<<"\t"<<name<<"\t"<<quantity<<"\t"<<limit_order<<"\t"<<"buy"<<"\t"<<"Cancelled"<<endl;
                        return price;
                    case 50:
                        {//obj1<<serial<<"    "<<quantity<<endl;
                        break;}
                    default:
                        cout<<"Wrong choice.";
                        break;
                    }
                }

                }
                if(price<=limit_order)
                {
                    obj<<serial<<"\t"<<name<<"\t"<<quantity<<"\t"<<price<<"\t"<<"buy"<<"\t"<<"Executed"<<endl;
                    obj1<<serial<<"    "<<name<<"    "<<quantity<<endl;
                    funds=funds-quantity*price;
                    //profit=profit-quantity*price;
                }
                while(stop_loss_price<price)
                {
                    system("cls");
                    cout<<serial<<"\t"<<name<<"    "<<quantity<<"    "<<stop_loss_price<<"    "<<price<<"    "<<"sell"<<endl;
                    cout<<"*****************************************************************"<<endl;
                    cout<<"1) Cancel this order."<<endl<<"2) Back to watchlist (WARNING: you won't be able to access this order again)"<<endl;
                    cout<<"*****************************************************************"<<endl;
                    price=pricing(price);
                    sleep(1);
                //obj1<<
                if(kbhit())
                {
                    x=getch();
                    if(x==49)
                    {
                        obj<<serial<<"\t"<<name<<"\t"<<quantity<<"\t"<<stop_loss_price<<"\t"<<"sell"<<"\t"<<"Cancelled"<<endl;
                        return price;
                    }
                    else if(x==50)
                    {//obj1<<serial<<"    "<<name<<"    "<<quantity<<endl;
                        break;}
                    else
                        cout<<"Wrong choice."<<endl;
                }

                }
                if(price<=stop_loss_price)
                {
                    obj<<serial<<"\t"<<name<<"\t"<<quantity<<"\t"<<price<<"\t"<<"sell"<<"\t"<<"Executed"<<endl;
                    obj1<<serial<<"    "<<name<<"    -"<<quantity<<endl;
                    funds=funds+quantity*price;
                    //profit=profit+quantity*price;
                }
            }
            else
            {
                ofstream obj;
                obj.open("order_class.txt",ios::app);
                obj<<serial<<"\t"<<name<<"\t"<<quantity<<"\t"<<limit_order<<"\t"<<"buy"<<"\t"<<"Rejected."<<endl;
            }
        }
        else
        {
            ofstream obj;
            obj.open("order_class.txt",ios::app);
            obj<<serial<<"\t"<<name<<"\t"<<quantity<<"\t"<<limit_order<<"\t"<<"buy"<<"\t"<<"Rejected."<<endl;
            cout<<"Not enough funds."<<endl;
            cout<<"1) Add more funds."<<endl<<"2) Back to watchlist"<<endl;
            cin>>x;
            if(x==1)
                add_funds();
            else if(x==2)
                return price;
        }
        return price;
    }
    void order_history()
    {
        ifstream obj;int x;
        obj.open("order_class.txt");
        string str;
        stack<string> s1;
        cout<<"*****************************************************************"<<endl;
        getline(obj,str);
        while(!obj.eof())
        {
            getline(obj,str);
            if(!obj.eof())
            {
                s1.push(str);
            }
        }
        while(!s1.empty())
        {
            if(!s1.empty())
            cout<<s1.top()<<endl;
            s1.pop();
        }
        cout<<"*****************************************************************"<<endl;
        cout<<"Enter any digit to return: ";
        cin>>x;
    }
};
void hii()
{
    cout<<"******************************************"<<endl;
    cout<<"************** STOCK MARKET **************"<<endl;
    cout<<"******************************************"<<endl<<endl;
}
void intro()
{
        cout<<"________________________________________________"<<endl;
        cout<<"This is your basic profile." <<endl<<"Let's add some funds in your account."<<endl<<"You can make changes whenever required."<<endl;
        cout<<"________________________________________________"<<endl<<endl;
}
template<class T>
class node
{

public:
    T data;
    node<T> *next;
    node()
    {
        data=nullptr;
        next=NULL;
    }
    node(T d)
    {
        data=d;
        next=NULL;
    }
    void add(node<T>*&head, T d)
    {
        node<T> *temp=new node(d);
        if(head==NULL)
        {
            head=temp;
        }
        else
        {
            node<T> *temp1=head;
            while(temp1->next!=NULL)
                temp1=temp1->next;
            temp1->next=temp;
        }
    }
    void delete1(node<T>*&head, T d)
    {
        node<T>* prev=NULL;
        node<T>*temp1=head;
        if(temp1->data==d)
            head=temp1->next;
        else
        {
            while(temp1->next!=NULL || temp1->data!=d)
        {
            prev=temp1;
            temp1=temp1->next;
        }
        prev->next=temp1->next;
        temp1->next=NULL;
        }
    }
    void print(node<T>*&head,int pos)
    {
        int y=1;
        if(pos==1)
        {
            cout<<head->data;
        }
        else
        {
            node<T> *temp=head;
            while(y<pos)
            {
                temp=temp->next;
                y++;
            }
            cout<<temp->data;
        }
    }
    T printf(node<T>*head,int pos)
    {
        int y=1;
        if(pos==1)
        {
            return head->data;
        }
        else
        {
            node<T> *temp=head;
            while(y<pos)
            {
                temp=temp->next;
                y++;
            }
            return temp->data;
        }
    }
    void update(node<T>*&head,T value, int pos)
    {
        node<T> *temp=head;int y=1;
        if(pos==1)
        {
            temp->data=value;
        }
        else
        {
            while(y<pos)
            {
                temp=temp->next;
                y++;
            }
            temp->data=value;
        }
    }
};
class watchlist
{
    static int count_watchlist;
    public:
    void print_stocks()
    {
        ifstream obj1;
        string str;
        obj1.open("stocks.txt");
        cout<<endl;
        while(!obj1.eof())
        {
            getline(obj1,str);
            cout<<str<<endl;
        }
        obj1.close();
    cout<<"-----------------------------------------------"<<endl;
    }
    void check()
    {
        char ch;
        ifstream obj;
        obj.open("count_watchlist.txt");
        obj.get(ch);
        //cout<<ch;
        int z=(int)ch;
        //cout<<z;
        count_watchlist=z-48;
        obj.close();
        int x=0;int y;
        if(count_watchlist==0)
        {
            cout<<endl<<"Let's start by creating a watchlist:"<<endl;
            create_watchlist(1);
        }
        else if(count_watchlist<3)
        {
            cout<<endl<<"1) Open a watchlist"<<endl<<"2) Create another watchlist"<<endl;
            cin>>x;
            if(x==1)
            {
                cout<<"Enter the id of watchlist you want to open: ";
                cin>>y;
                if(y>0&&y<=count_watchlist)
                    print_watchlist(y);
                else
                    check();
            }
            else if(x==2)
                create_watchlist(count_watchlist+1);
            else
            {
                cout<<"Sorry wrong choice.Enter Again"<<endl;
                check();
            }
        }
        else if(count_watchlist==3)
        {

            cout<<"Enter the id of watchlist you want to open: ";
            cin>>y;
            if(y>0&&y<=count_watchlist)
                print_watchlist(y);
            else
                check();
        }

    }
    void print_watchlist(int key)
    {
        ifstream obj1;int x,count=0;
        string str;
        if(key==1)
                obj1.open("watchlist1.txt");
            else if(key==2)
                obj1.open("watchlist2.txt");
            else if(key==3)
                obj1.open("watchlist3.txt");

            node<int> * head_serial=NULL;
           node<string>* head_name=NULL;
           node<double>* head_price=NULL;
           int s1,s2;
           char a[100],b[1];
           while(!obj1.eof())
           {
                string str2="";
                getline(obj1,str);
                for(int i=0;i<str.length();i++)
                    a[i]=str[i];
                s1=stoi(a);

                for(int i=4;i<28;i++)
                    str2=str2+str[i];

                for(int i=28;i<str.length();i++)
                    b[i-28]=str[i];
                    s2=stoi(b);

                //if(!obj1.eof())
                //cout<<s1<<"\t"<<str2<<"\t"<<s2<<endl;

                if(!obj1.eof())
                {head_serial->add(head_serial,s1);
                head_name->add(head_name,str2);
                head_price->add(head_price,s2);
                count++;}

                /*if(!obj1.eof())
                {
                    head_serial->print(head_serial);
                cout<<endl;
                head_name->print(head_name);
                cout<<endl;
                head_price->print(head_price);
                cout<<endl;*/
                //str2="";
                //str="";
            }

            int d=0;int s;string word;int count1=0,count2=0;int stck;
            while(true)
            {
                if(d==0)
                    system("cls");
                else
                    d=0;

                cout<<"**************************************************************"<<endl;
                for(int i=1;i<=count;i++)
                {
                    head_serial->print(head_serial,i);
                    cout<<".  ";
                    head_name->print(head_name,i);
                    cout<<"     ";
                    head_price->print(head_price,i);
                    cout<<endl;
                }
                cout<<"**************************************************************"<<endl;
                cout<<"______________________________________________________________"<<endl;
                cout<<endl<<"1) Add a stock"<<endl<<"2) Delete a stock"<<endl<<"3) Switch watchlist."<<endl<<"4) Place an order"<<endl<<"5) Executed orders"<<endl<<"6) view account"<<endl<<"7) add/withdraw funds"<<endl;
                for(int i=1;i<=count;i++)
                {
                    node<double>* temp=head_price;
                    for(int j=1;j<i;j++)
                        temp=temp->next;
                    temp->data=pricing(temp->data);
                }

                ofstream o;

                            if(key==1)
                                o.open("watchlist1.txt");
                            else if(key==2)
                                o.open("watchlist2.txt");
                            else if(key==3)
                                o.open("watchlist3.txt");
                            for(int i=1;i<=count;i++)
                            {
                                o<<head_serial->printf(head_serial,i)<<".  "<<head_name->printf(head_name,i)<<head_price->printf(head_price,i)<<endl;
                            }
                sleep(1);
                if(kbhit())
                {

                    d=getch();

                    switch(d)
                    {


                        case 49:
                            {system("cls");
                            add(key);
                            print_watchlist(key);
                            d=49;
                            break;}
                        case 50:
                            {system("cls");
                            delete1(key);
                            print_watchlist(key);
                            d=50;
                            break;}
                        case 51:
                            {system("cls");
                            check();
                            //print_watchlist(key);
                            d=51;
                            break;}
                        case 52:
                            {system("cls");
                            cout<<"***************************************************"<<endl;
                                ifstream o;
                                if(key==1)
                                    o.open("watchlist1.txt");
                                else if(key==2)
                                    o.open("watchlist2.txt");
                                else if(key==3)
                                    o.open("watchlist3.txt");
                                while(!o.eof())
                                {
                                    getline(o,str);
                                    if(!o.eof())
                                    cout<<str<<endl;
                                }
                                o.close();
                                cout<<"***************************************************"<<endl;
                            cout<<"Choose a stock: ";
                            cin>>stck;
                            ifstream obj5;
                            if(key==1)
                                obj5.open("watchlist1.txt");
                            else if(key==2)
                                obj5.open("watchlist2.txt");
                            else if(key==3)
                                obj5.open("watchlist3.txt");
                            while(!obj5.eof())
                            {
                                obj5>>word;
                                s=stoi(word);
                                getline(obj5,str);
                                count1++;
                                if(s==stck)
                                {
                                    count2++;
                                    break;
                                }
                            }
                            if(count2==0)
                                cout<<"Stock Not found";
                            else
                            {

                                double p;
                                order abcd( head_serial->printf(head_serial,count1) , head_name->printf(head_name,count1) , head_price->printf(head_price,count1) );
                                p=abcd.order_choice();
                                head_price->update(head_price,p,count1);
                            }
                            d=52;
                            print_watchlist(key);
                            break;}
                        case 53:
                            {
                                system("cls");
                                order a;
                                a.order_history();
                                print_watchlist(key);
                                d=53;
                                break;
                            }
                        case 54:
                            {system("cls");
                            print_account();
                            print_watchlist(key);
                            d=54;
                            break;}
                        case 55:
                            {
                                system("cls");
                                choice();
                                print_watchlist(key);
                                d=55;
                                break;
                            }
                       /*default:
                            d=0;
                            break;*/
                    }
                }
            }
         /*for(int i=1;i<=count;i++)
         {
             head_serial->print(head_serial,i);
             cout<<".)\t";
             head_name->print(head_name,i);
             head_price->print(head_price,i);
             cout<<endl;
         }*/
       /* while(!obj1.eof())
        {
            getline(obj1,str);
            cout<<str<<endl;
        }*/
        obj1.close();

    }
    void create_watchlist(int key)
    {
            string str;int flag=1;
            ofstream obj2;
            if(key==1)
                obj2.open("watchlist1.txt");
            else if(key==2)
                obj2.open("watchlist2.txt");
            else if(key==3)
                obj2.open("watchlist3.txt");
            while(flag)
            {
                ifstream obj1;
                obj1.open("stocks.txt");
                int x=0;
                cout<<"Add a stock to the watchlist: (enter 0 to exit) ";
                cin>>x;
                x=x+3;
                int y=1;
                if(x!=3)
                {
                    while(!obj1.eof() && y<=x)
                    {
                        getline(obj1,str);
                        if(y==x)
                            obj2<<str<<endl;
                        y++;
                    }
                    obj1.close();
                }
                else
                {
                    flag=0;
                    count_watchlist++;
                    ofstream obj;
                    obj.open("count_watchlist.txt");
                    obj<<count_watchlist<<endl;
                    obj.close();
                }
            }
            check();
    }
    void add(int key)
    {
        string str;
        /*fstream obj;
    if(key==1)
            obj.open("watchlist1.txt",ios::in | ios::out | ios::app);
        else if(key==2)
            obj.open("watchlist2.txt",ios::in | ios::out | ios::app);
        else if(key==3)
            obj.open("watchlist3.txt",ios::in | ios::out | ios::app);
    char a[1000],b[10];int s1,s2;
    while(!obj.eof())
    {
        string str2;
                getline(obj,str);
               /*for(int i=0;i<str.length();i++)
                    a[i]=str[i];
                s1=stoi(a);

                for(int i=4;i<28;i++)
                    str2=str2+str[i];

                for(int i=28;i<str.length();i++)
                    b[i-28]=str[i];
                    s2=stoi(b);

                if(!obj.eof())
                cout<<s1<<"\t"<<str2<<"\t"<<s2<<endl;
                cout<<str<<endl;
    }
    obj.close();*/
    ifstream obj;
    obj.open("stocks.txt");
    cout<<endl;
    while(!obj.eof())
    {
        getline(obj,str);
        cout<<str<<endl;
    }
    obj.close();
    fstream obj2;
    if(key==1)
            obj2.open("watchlist1.txt",ios::in | ios::out | ios::app);
        else if(key==2)
            obj2.open("watchlist2.txt",ios::in | ios::out | ios::app);
        else if(key==3)
            obj2.open("watchlist3.txt",ios::in | ios::out | ios::app);
    int x;int s;string word;
    cout<<"Enter the serial number you want to add:";
    cin>>x;
    int count=0;
    if(x>0&&x<=50)
    {while(!obj2.eof())
    {
        obj2>>word;
        s=stoi(word);
        getline(obj2,str);
        if(s==x)
        {
            cout<<"already exists"<<endl;
            count++;
            break;
        }
    }
    obj2.close();
    fstream obj3;
    if(key==1)
            obj3.open("watchlist1.txt",ios::in | ios::out | ios::app);
        else if(key==2)
            obj3.open("watchlist2.txt",ios::in | ios::out | ios::app);
        else if(key==3)
            obj3.open("watchlist3.txt",ios::in | ios::out | ios::app);
    if(count==0)
    {   //cout<<"1";
        fstream obj1;
        obj1.open("stocks.txt",ios::in|ios::out|ios::app);
        x=x+3;int y=1;

            while(!obj1.eof() && y<=x)
            {   //cout<<"2";
                getline(obj1,str);
                if(y==x)
                {
                    cout<<"Stock added sucessfully"<<endl;
                    obj3<<str<<endl;
                }
                y++;
            }

    }
    }
    else{
        cout<<"Wrong choice enter again"<<endl;
        add(key);
    }
    }

    void delete1(int key)
    {
        string word,str,str2;
        int s1,s2,x,count=0;
        char a[1000],b[10];
        cout<<"***************************************************"<<endl;
        ifstream o;
        if(key==1)
            o.open("watchlist1.txt");
        else if(key==2)
            o.open("watchlist2.txt");
        else if(key==3)
            o.open("watchlist3.txt");
            while(!o.eof())
            {
                getline(o,str);
                if(!o.eof())
                cout<<str<<endl;
            }
            o.close();
            cout<<"***************************************************"<<endl;
        fstream obj1;
        if(key==1)
            obj1.open("watchlist1.txt",ios::in | ios::out | ios::app);
        else if(key==2)
            obj1.open("watchlist2.txt",ios::in | ios::out | ios::app);
        else if(key==3)
            obj1.open("watchlist3.txt",ios::in | ios::out | ios::app);
        ofstream obj2;
        obj2.open("temporary.txt");
        cout<<"Enter the serial number you want to delete: ";
        cin>>x;
        while(!obj1.eof())
        {
            getline(obj1,str);
               for(int i=0;i<str.length();i++)
                    a[i]=str[i];
                s1=stoi(a);

                for(int i=4;i<28;i++)
                    str2=str2+str[i];

                for(int i=28;i<str.length();i++)
                    b[i-28]=str[i];
                    s2=stoi(b);
            if(s1==x)
            {
                count++;
                s1=0;s2=0;str2="";str="";
                continue;
            }
            if(!obj1.eof())
                obj2<<s1<<".  "<<str2<<s2<<endl;
            s1=0;s2=0;str2="";str="";
        }
        obj2.close();
        ifstream obj3;
        obj3.open("temporary.txt");
        ofstream obj4;
        if(key==1)
            obj4.open("watchlist1.txt");
        else if(key==2)
            obj4.open("watchlist2.txt");
        else if(key==3)
            obj4.open("watchlist3.txt");

        while(!obj3.eof())
        {
            getline(obj3,str);
            if(!obj3.eof())
            obj4<<str<<endl;
        }
        if(count==0)
        {
            cout<<"Stock not present."<<endl;
        }
        else
        {
            cout<<"Watchlist updated."<<endl;
        }
    }
};
int watchlist::count_watchlist=0;
int main()
{
   hii();

   intro();
   details();
    profit=funds;

   //a1->choice();
   watchlist a;
   a.print_stocks();
   a.check();
    //a.add(1);
   //a.create_watchlist();
}
