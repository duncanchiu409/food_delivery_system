// Food Delivery System
// The system at most stores 100 food orders and 20 drivers.
#include <iostream>
#include <string>
int food_order_count=0;
int driver_count=0;

void uiInterface(){
    std::cout<<"************************"<<std::endl;
    std::cout<<"*** Main Menu ***"<<std::endl;
    std::cout<<"[1] Single input"<<std::endl;
    std::cout<<"[2] Batch input"<<std::endl;
    std::cout<<"[3] Show information"<<std::endl;
    std::cout<<"[4] Assign drivers"<<std::endl;
    std::cout<<"[5] Credits and Exit"<<std::endl;
    std::cout<<"************************"<<std::endl;
    std::cout<<"Option (1-5) : ";
}

void singleInput(){
    std::cout<<"************************"<<std::endl;
    std::cout<<"*** Single input ***"<<std::endl;
    std::cout<<"[1] Adding a new food order"<<std::endl;
    std::cout<<"[2] Adding a new driver record"<<std::endl;
    std::cout<<"[3] Exit"<<std::endl;
    std::cout<<"************************"<<std::endl;
    std::cout<<"Option (1-3) : ";
}

void batchInput(){
    std::cout<<"************************"<<std::endl;
    std::cout<<"*** Batch input ***"<<std::endl;
    std::cout<<"[1] Adding multiple new food orders"<<std::endl;
    std::cout<<"[2] Adding multiple new driver records"<<std::endl;
    std::cout<<"[3] Exit"<<std::endl;
    std::cout<<"************************"<<std::endl;
    std::cout<<"Option (1-3) : ";
}

void showInformation(){
    std::cout<<"************************"<<std::endl;
    std::cout<<"*** Show Info Menu ***"<<std::endl;
    std::cout<<"[1] Show all food orders"<<std::endl;
    std::cout<<"[2] Show all drivers"<<std::endl;
    std::cout<<"[3] Show one driver by ID"<<std::endl;
    std::cout<<"[4] Return to Main Menu"<<std::endl;
    std::cout<<"************************"<<std::endl;
    std::cout<<"Option (1-4) : ";
}

void assignDrivers(){
    std::cout<<"************************"<<std::endl;
    std::cout<<"*** Assign Drivers Menu ***"<<std::endl;
    std::cout<<"[1] Assign drivers manually"<<std::endl;
    std::cout<<"[2] Assign drivers automatically"<<std::endl;
    std::cout<<"[3] Return Main Menu"<<std::endl;
    std::cout<<"************************"<<std::endl;
    std::cout<<"Option (1-3) : "<<std::endl;
}

bool checkTimeFormat(std::string time){
    int length=time.length();
    if(length!=5){
        std::cout<<"************************"<<std::endl;
        std::cout<<"Having error with invalid format."<<std::endl;
        /*if(time[2]!=':'){
            std::cout<<"************************"<<std::endl;
            std::cout<<"Having error with invalid format."<<std::endl;
        }*/
        return false;
    }
    if(time[2]!=':'){
        std::cout<<"************************"<<std::endl;
        std::cout<<"Having error with invalid format."<<std::endl;
        return false;
    }
    return true;
}

int changeTimeToInteger(std::string time){
    std::string tmp;
    tmp=time.replace(2,1,"0");
    return std::stoi(tmp);
}

class foodOrder{
    public:
        int ID;
        std::string order_title;
        std::string food_pickup_time;
        int delivery_duration;
        bool assigned_driver;

        foodOrder(){
            ID=food_order_count+1;
            order_title="";
            food_pickup_time="";
            delivery_duration=0;
            assigned_driver=false;
        }

        void showFoodOrderInfo(){
            std::cout<<"************************"<<std::endl;
            std::cout<<"*** Food Order ***"<<std::endl;
            std::cout<<"ID : "<<ID<<std::endl;
            std::cout<<"Order Title : "<<order_title<<std::endl;
            std::cout<<"Food Pick Up Time : "<<food_pickup_time<<std::endl;
            std::cout<<"Delivery Duration : "<<delivery_duration<<" mins"<<std::endl;
            std::cout<<"Assigned : "<<assigned_driver<<std::endl;
        }
};

std::string returnEndOrderTime(foodOrder a){
    int start=changeTimeToInteger(a.food_pickup_time);
    start+=a.delivery_duration;
    int minute_part=start%1000;
    int hour_part=start/1000;
    if(minute_part/60!=0){
        hour_part+=minute_part/60;
        minute_part=minute_part%60;
    }

    std::string result="";
    if(hour_part/10==0){
        result+="0";
    }
    result+=std::to_string(hour_part);
    result+=":";
    if(minute_part/10==0){
        result+="0";
    }
    result+=std::to_string(minute_part);
    return result;
}

class driverFoodDelivery{
    public:
        int ID;
        std::string driver_name;
        std::string working_hour_from;
        std::string working_hour_to;
        foodOrder his_food_order[10];
        int his_food_order_count;
        int salary;

        driverFoodDelivery(){
            ID=driver_count+1;
            driver_name="";
            working_hour_from="";
            working_hour_to="";
            his_food_order_count=0;
            salary=0;
        }

        void insertAFoodOrder(foodOrder A){
            his_food_order[his_food_order_count]=A;
            his_food_order_count++;
            sortFoodOrders();
        }
        
        void sortFoodOrders(){
            // assuming all food orders will not crash.
            if(his_food_order_count==0){
                return;
            }
            // sorting his food orders.
            foodOrder* temp=new foodOrder[1];
            for(int i=0;i<his_food_order_count;i++){
                for(int j=i;j<his_food_order_count;j++){
                    if(changeTimeToInteger(his_food_order[i].food_pickup_time)>changeTimeToInteger(his_food_order[j].food_pickup_time)){
                        temp[0]=his_food_order[i];
                        his_food_order[i]=his_food_order[j];
                        his_food_order[j]=temp[0];
                    }
                }
            }
        }

        void showFreeTimeSlots(){
            std::cout<<"************************"<<std::endl;
            std::cout<<"*** Free Time Slot ***"<<std::endl;
            if(his_food_order_count==0){
                std::cout<<working_hour_from<<"-"<<working_hour_to<<std::endl;
                return;
            }
            else{
                if(changeTimeToInteger(his_food_order[0].food_pickup_time)!=changeTimeToInteger(working_hour_from)){
                    std::cout<<working_hour_from<<"-"<<his_food_order[0].food_pickup_time<<std::endl;
                }
                for(int i=0;i<his_food_order_count;i++){
                    //std::cout<<mike.his_food_order[i].food_pickup_time<<std::endl;
                    if((i+1)!=his_food_order_count){
                        std::cout<<returnEndOrderTime(his_food_order[i])<<"-"<<his_food_order[i+1].food_pickup_time<<std::endl;
                    }
                }
                if(changeTimeToInteger(returnEndOrderTime(his_food_order[his_food_order_count-1]))!=changeTimeToInteger(working_hour_to)){
                    std::cout<<returnEndOrderTime(his_food_order[his_food_order_count-1])<<"-"<<working_hour_to<<std::endl;
                }
            }
        }

        void showDriverInfo(){
            std::cout<<"************************"<<std::endl;
            std::cout<<"Driver ID : "<<ID<<std::endl;
            std::cout<<"Driver Name : "<<driver_name<<std::endl;
            std::cout<<"Working Hour (From) : "<<working_hour_from<<std::endl;
            std::cout<<"Working Hour (To) : "<<working_hour_to<<std::endl;
        }
};

// check if check time format is excessive.
bool checkTimeRange(std::string time){
    if(!checkTimeFormat(time)){
        return false;
    }
    time.replace(2,1,"0");
    int number=std::stoi(time);
    //std::cout<<number<<std::endl;
    if(number<7000||number>20000){
        std::cout<<"************************"<<std::endl;
        std::cout<<"Please kindly re-enter. Having error with invalid time range."<<std::endl;
        return false;
    }
    return true;
}


bool checkBatchInput(std::string input){
    int slash_count=0;
    int length=input.length();

    std::string time="";
    for(int i=0;i<length;i++){
        if(input[i]=='/'){
            slash_count++;
        }
    }
    //std::cout<<"slash count : "<<slash_count<<std::endl;
    if(slash_count!=2)return false;

    int x=input.find("/");
    if(x!=std::string::npos){
        time=input.substr(x+1,5);
        //std::cout<<"time : "<<time<<std::endl;
        if(!checkTimeRange(time))return false;
    }
    return true;
    // check if X is integer.
}

// change later, too complicated.
std::string promptTime(std::string type){
    std::string input="";
    std::getline(std::cin,input);
    while(!checkTimeRange(input)){
        std::cout<<"************************"<<std::endl;
        std::cout<<type<<" : ";
        std::getline(std::cin,input);
    }
    return input;
}


bool checkFree(driverFoodDelivery a,foodOrder b){
    if(b.assigned_driver==true){
        return false;
    }

    int start=changeTimeToInteger(b.food_pickup_time);
    int end=changeTimeToInteger(returnEndOrderTime(b));

    // compare working hours of driver
    if(changeTimeToInteger(a.working_hour_from)>start)return false;
    if(changeTimeToInteger(a.working_hour_to)<end)return false;

    int tmp_start=0;
    int tmp_end=0;
    // compare food orders of drivers.
    for(int i=0;i<a.his_food_order_count;i++){
        tmp_start=changeTimeToInteger(a.his_food_order[i].food_pickup_time);
        tmp_end=changeTimeToInteger(returnEndOrderTime(a.his_food_order[i]));

        if(!(start<tmp_start&&end<=tmp_end)||!(tmp_end>=start&&tmp_end>end))return false;
    }
    return true;  
}

void showAvailableFoodOrders(foodOrder a[],driverFoodDelivery b){
    std::cout<<"************************"<<std::endl;
    std::cout<<"*** Available Food Orders ***"<<std::endl;
    for(int i=0;i<food_order_count;i++){
        if(checkFree(b,a[i])&&a[i].assigned_driver==false){
            a[i].showFoodOrderInfo();
        }
    }
}

void insertAvailableFoodOrders(driverFoodDelivery a[], foodOrder b[]){
    std::cout<<"************************"<<std::endl;
    std::cout<<"*** Inserted Food Orders ***"<<std::endl;
    for(int j=0;j<driver_count;j++){
        for(int i=0;i<food_order_count;i++){
            if(checkFree(a[j],b[i])){
                b[i].assigned_driver=true;
                a[j].insertAFoodOrder(b[i]);
                a[j].his_food_order[a[j].his_food_order_count].showFoodOrderInfo();
            }
        }
    }
}

int main(){
    foodOrder A[100];

    driverFoodDelivery B[100];
    

    std::string input;
    int command=-1;

    while(true){
        uiInterface();
        std::cin>>input;
        command=std::stoi(input);

        int error_trial=3;
        switch(command){
            case 1:
                while(command!=3){
                    singleInput();
                    std::cin>>input;
                    command=std::stoi(input);
                    std::cin.ignore();
                    switch(command){
                        case 1:
                            std::cout<<"************************"<<std::endl;
                            std::cout<<"*** Adding a new food order ***"<<std::endl;
                            std::cout<<"There are three information to input"<<std::endl;
                            std::cout<<"[1] Order Title"<<std::endl;
                            std::cout<<"[2] Food Pickup Time"<<std::endl;
                            std::cout<<"[3] Delivery Duration"<<std::endl;
                            std::cout<<"************************"<<std::endl;
                            A[food_order_count].ID=food_order_count+1;
                            std::cout<<"Food Order ID : "<<A[food_order_count].ID<<std::endl;
                            std::cout<<"Orde Title : ";
                            std::getline(std::cin,input);
                            // check correctness
                            A[food_order_count].order_title=input;
                            std::cout<<"Food Pickup Time : ";
                            input=promptTime("Food Pickup Time");
                            A[food_order_count].food_pickup_time=input;
                            std::cout<<"Delivery Duration : ";
                            std::getline(std::cin,input);
                            // check correctness
                            A[food_order_count].delivery_duration=std::stoi(input);

                            food_order_count++;
                            break;
                        case 2:
                            std::cout<<"************************"<<std::endl;
                            std::cout<<"*** Adding a new driver record ***"<<std::endl;
                            std::cout<<"There are three information to input"<<std::endl;
                            std::cout<<"[1] Driver Name"<<std::endl;
                            std::cout<<"[2] Working Hour (From)"<<std::endl;
                            std::cout<<"[3] Working Hour (To)"<<std::endl;
                            std::cout<<"************************"<<std::endl;
                            B[driver_count].ID=driver_count+1;
                            std::cout<<"Driver ID : "<<B[driver_count].ID<<std::endl;
                            std::cout<<"Driver Name : ";
                            std::getline(std::cin,input);
                            // check correctness
                            B[driver_count].driver_name=input;
                            std::cout<<"Working Hour (From) : ";
                            input=promptTime("Working Hour (From)");
                            B[driver_count].working_hour_from=input;
                            std::cout<<"Working Hour (To) : ";
                            input=promptTime("Working Hour (To)");
                            B[driver_count].working_hour_to=input;

                            driver_count++;
                            break;
                        case 3:
                            std::cout<<"************************"<<std::endl;
                            std::cout<<"Option 3. Back to Main Menu."<<std::endl;
                            break;
                        default:
                            error_trial--;
                            std::cout<<"************************"<<std::endl;
                            std::cout<<"Option must be between 1-3."<<std::endl;
                            break;
                    }
                    if(error_trial==0){
                        std::cout<<"************************"<<std::endl;
                        std::cout<<"Failed 3 times. Back to Main Menu."<<std::endl;
                        break;
                    }
                }
                error_trial=3;
                break;
            case 2:
                while(command!=3){
                    batchInput();
                    std::cin>>input;
                    command=std::stoi(input);
                    switch(command)
                    {
                    case 1:
                        std::cout<<"************************"<<std::endl;
                        std::cout<<"Adding multiple new food orders"<<std::endl;
                        std::cin.ignore();
                        while(input.compare("0")){
                            std::cout<<"************************"<<std::endl;
                            getline(std::cin,input);
                            if(checkBatchInput(input)){
                                std::cout<<"************************"<<std::endl;
                                A[food_order_count].ID=food_order_count+1;
                                std::cout<<"Food Order ID : "<<A[food_order_count].ID<<std::endl;
                                int x=input.find("/");
                                A[food_order_count].order_title=input.substr(0,x);
                                std::cout<<"order title : "<<A[food_order_count].order_title<<std::endl;
                                A[food_order_count].food_pickup_time=input.substr(x+1,5);
                                std::cout<<"food pickup time : "<<A[food_order_count].food_pickup_time<<std::endl;
                                A[food_order_count].delivery_duration=std::stoi(input.substr(x+7));
                                std::cout<<"delivery duration : "<<A[food_order_count].delivery_duration<<std::endl;
                                food_order_count++;
                            }
                            else if(!input.compare("0"))break;
                            else{
                                std::cout<<"************************"<<std::endl;
                                std::cout<<"Explanation:"<<std::endl;
                                std::cout<<"Information of one food order is put in the order: Order Title, Food Pickup Time, Delivery Duration (X is an integer), separated by ‘/’."<<std::endl;
                                std::cout<<"Example:\nGreat Mirror Lunch Set/12:30/40\nJohn’s Order/11:50/30"<<std::endl;
                            }
                        }
                        break;
                    case 2:
                        std::cout<<"************************"<<std::endl;
                        std::cout<<"Adding multiple new driver records"<<std::endl;
                        std::cin.ignore();
                        while(input.compare("0")){
                            std::cout<<"************************"<<std::endl;
                            getline(std::cin,input);
                            if(checkBatchInput(input)){
                                std::cout<<"************************"<<std::endl;
                                B[driver_count].ID=driver_count+1;
                                std::cout<<"Driver ID : "<<B[driver_count].ID<<std::endl;
                                int x=input.find("/");
                                B[driver_count].driver_name=input.substr(0,x);
                                std::cout<<"driver name : "<<B[driver_count].driver_name<<std::endl;
                                B[driver_count].working_hour_from=input.substr(x+1,5);
                                std::cout<<"working hour from : "<<B[driver_count].working_hour_from<<std::endl;
                                B[driver_count].working_hour_to=input.substr(x+7);
                                std::cout<<"working hour to : "<<B[driver_count].working_hour_to<<std::endl;
                                driver_count++;
                            }
                            else if(!input.compare("0"))break;
                            else{
                                std::cout<<"************************"<<std::endl;
                                std::cout<<"Explanation:"<<std::endl;
                                std::cout<<"Information of one food order is put in the order: Order Title, Food Pickup Time, Delivery Duration (X is an integer), separated by ‘/’."<<std::endl;
                                std::cout<<"Example:\nGreat Mirror Lunch Set/12:30/40\nJohn’s Order/11:50/30"<<std::endl;
                            }
                        }
                        break;
                    case 3:
                        std::cout<<"************************"<<std::endl;
                        std::cout<<"Option 3. Back to Main Menu."<<std::endl;
                        break;
                    default:
                        error_trial--;
                        std::cout<<"************************"<<std::endl;
                        std::cout<<"Option must be between 1-3."<<std::endl;
                        break;
                    }
                }
                error_trial=3;
                break;
            case 3:
                while(command!=4){
                    showInformation();
                    std::cin>>input;
                    command=std::stoi(input);
                    switch(command)
                    {
                        case 1:
                            std::cout<<"************************"<<std::endl;
                            std::cout<<"Food Order List"<<std::endl;
                            for(int i=0;i<food_order_count;i++){
                                A[i].showFoodOrderInfo();
                            }
                            break;
                        case 2:
                            std::cout<<"************************"<<std::endl;
                            std::cout<<"Driver List"<<std::endl;
                            for(int i=0;i<driver_count;i++){
                                B[i].showDriverInfo();
                            }
                            break;
                        case 3:
                            std::cout<<"************************"<<std::endl;
                            std::cout<<"Driver ID : ";
                            std::cin>>input;
                            int driver_id;
                            driver_id=std::stoi(input);
                            
                            B[driver_id-1].showFreeTimeSlots();
                            // salary.
                        case 4:
                            std::cout<<"************************"<<std::endl;
                            std::cout<<"Option 4. Back to Main Menu"<<std::endl;
                            break;
                        default:
                            error_trial--;
                            std::cout<<"************************"<<std::endl;
                            std::cout<<"Option must be between 1-4."<<std::endl;
                            break;
                    }
                    if(error_trial==0){
                        std::cout<<"************************"<<std::endl;
                        std::cout<<"Failed 3 times. Back to Main Menu."<<std::endl;
                        break;
                    }
                }
                error_trial=3;
                break;
            case 4:
                int driver_id;
                int foodID;
                int count;
                while(command!=3){
                    assignDrivers();
                    std::cin>>input;
                    command=std::stoi(input);
                    std::cin.ignore();
                    
                    switch(command){
                        case 1:
                            std::cout<<"************************"<<std::endl;
                            std::cout<<"Assign driver manually"<<std::endl;
                            std::cout<<"************************"<<std::endl;
                            std::cout<<"Driver ID : ";
                            std::cin>>input;
                            driver_id=std::stoi(input);
                            if(driver_id>driver_count){
                                std::cout<<"************************"<<std::endl;
                                std::cout<<"Such Driver ID dont exist in server."<<std::endl;
                                break;
                            }
                            B[driver_id-1].showDriverInfo();
                            B[driver_id-1].showFreeTimeSlots();

                            showAvailableFoodOrders(A,B[driver_id-1]);
                            foodID=0;
                            std::cout<<"************************"<<std::endl;
                            std::cout<<"Food ID : ";
                            std::cin>>input;
                            foodID=std::stoi(input);
                            A[foodID-1].assigned_driver=true;
                            B[driver_id-1].insertAFoodOrder(A[foodID]);
                            B[driver_id-1].his_food_order[B[driver_id-1].his_food_order_count].showFoodOrderInfo();
                            break;
                        case 2:
                            insertAvailableFoodOrders(B,A);
                            break;
                        case 3:
                            std::cout<<"************************"<<std::endl;
                            std::cout<<"Option 3. Back to Main Menu"<<std::endl;
                            break;
                        default:
                            error_trial--;
                            std::cout<<"************************"<<std::endl;
                            std::cout<<"Option must be between 1-3."<<std::endl;
                            break;
                    }
                    if(error_trial==0){
                        std::cout<<"************************"<<std::endl;
                        std::cout<<"Failed 3 times. Back to Main Menu."<<std::endl;
                        break;
                    }
                }
                error_trial=3;
                break;
            case 5: // R5 Credits and Exit
                while(true){
                    std::cout<<"************************"<<std::endl;
                    std::cout<<"Exit : "<<std::endl;
                    std::cin.ignore();
                    std::getline(std::cin,input);
                    switch(input[0])
                    {
                        case 'Y':
                        case 'y':
                            std::cout<<"************************"<<std::endl;
                            std::cout<<"System Terminates"<<std::endl;
                            return 0;
                            break;
                        case 'N':
                        case 'n':
                            std::cout<<"************************"<<std::endl;
                            std::cout<<"Back to Main Menu"<<std::endl;
                            break;
                        default:
                            std::cout<<"************************"<<std::endl;
                            std::cout<<"Option must be Y or N"<<std::endl;
                            break;
                    }
                    if(!input.compare("Y")||!input.compare("y")){
                        return 0;
                    }
                    else{
                        break;
                    }
                }
                break;
            default:
                std::cout<<"************************"<<std::endl;
                std::cout<<"Option must be between 1-5."<<std::endl;
                break;
        }
    }
    
    return 0;
}