#include<iostream>
using namespace std;

class Device{
    //Private data members
    string name;
    bool isOn;
    int brightness;
    
    public:
    //Initializes device with default values
    Device(){
        name="Unknown";
        isOn=false;
        brightness=50;
    }
    //Initializes devices with user-provided values
    Device(string n, bool status, int b){
        name=n;
        isOn=status;
        //Validate brightness range (0-100)
        if(b>=0 && b<=100)
        brightness=b;
        else
        brightness=50;
    }
    //---Destructor---
    //Called automatically when object is destroyed
    ~Device(){
        cout<<"Device"<<name<<" is being removed."<<endl;
    }
    //Setter Functions
    void setName(string n){
        name=n;
    }

    void setBrightness(int b){
        if(b>=0 && b<=100)
        brightness=b;
        else
        cout<<"Invalid brightness! Must be between 0 and 100."<<endl;
    }
    //Getter Functions
    string getName()const{
        return name;
    }
    int getBrightness()const{
        return brightness;
    }
    bool getStatus()const{
        return isOn;
    }
    //Device Control Functions
    void turnOn(){
        isOn=true;
    }

    void turnOff(){
        isOn=false;
    }
    //Display Function
    void showInfo()const{
        cout<<"Name: "<<name<<", Status: "<<(isOn ? "ON" : "OFF")<<", Brightness: "<<brightness<<endl;
    }
};

class Room
{
    string roomName;
    Device devices[5];
    int count;

    public:
    //Constructor to initialize room
    Room(string name){
        roomName=name;
        count=0;
    }
    //Destructor
    ~Room(){
        cout<<"Room "<<roomName<<" manager closed."<<endl;
    }
    //Function to add device (object passed as argument)
    void addDevice(Device d){
        if (count<5)
        {
            devices[count]=d; //Store object in array
            count++;
            cout<<"Device added successfully!"<<endl;
        }
        else{
            cout<<"Room is full! Cannot add more devices."<<endl;
        }
    }
    //Display all devices
    void showAllDevices() const{
        if (count == 0){
            cout<<"No devices in the room."<<endl;
            return;
        }
        for(int i=0; i<count; i++){
            devices[i].showInfo();
        }
    }
    //Search device by name
    int findDevice(string name){
        for(int i=0; i<count; i++){
            if (devices[i].getName()==name)
            return i;
        }
        return -1; //Not found
    }

    void toggleDevice(string name){
        int index=findDevice(name);
        if (index == -1){
            cout<<"Device not found!"<<endl;
            return;
        }
        if (devices[index].getStatus()){
            devices[index].turnOff();
            cout<<"Device turned OFF."<<endl;
        }
        else
        {
            devices[index].turnOn();
            cout<<"Device turned ON."<<endl;
        }
    }
    //Change device brightness
    void setDeviceBrightness(string name, int brightness)
    {
        int index=findDevice(name);
        if (index == -1){
            cout<<"Device not found!"<<endl;
            return;
        }
        devices[index].setBrightness(brightness);
    }
};
//=============================
//Main Function
//=============================
int main()
{
    string roomName;
    //Take room name from user
    cout<<"Enter Room Name: ";
    getline(cin, roomName);
    //Create Room Object
    Room myRoom(roomName);

    int choice;
    //Menu-driven loop
    do
    {
     cout<<"\n=== Smart Room Manager ==="<<endl;
     cout<<"1. Add a Device"<<endl;
     cout<<"2. Show All Devices"<<endl; 
     cout<<"3. Turn Devices ON/OFF"<<endl; 
     cout<<"4. Change Brightness"<<endl; 
     cout<<"5. Exit"<<endl; 
     cout<<"Enter choice: ";
     cin>>choice;

     cin.ignore(); //Clear input buffer

     if (choice == 1)
     {
        string name;
        bool status;
        int brightness;

        cout<<"Enter device name: ";
        getline(cin, name);

        cout<<"Enter status (1 for ON, 0 for OFF): ";
        cin>>status;
        cout<<"Enter brightness (0-100) ";
        cin>>brightness;

        cin.ignore();
        //Create object using overloaded constructor
        Device newDevice(name, status, brightness);
        //Pass object to Room Function
        myRoom.addDevice(newDevice);
     }
     else if(choice == 2)
    {
        myRoom.showAllDevices();
    }
    else if (choice == 3)
    {
        string name;
        cout<<"Enter device name to toggle: ";
        getline(cin, name);
    }
    else if (choice == 4)
    {
        string name;
        int brightness;

        cout<<"Enter devices name: ";
        getline(cin, name);

        cout<<"Enter new brightness (0-100): ";
        cin>>brightness;

        cin.ignore();

        myRoom.setDeviceBrightness(name, brightness);
    }
    else if (choice == 5){
        cout<<"Existing program..."<<endl;
    }
    else{
        cout<<"Envalid choice. Try again."<<endl;
    }

    }
    while (choice != 5);
    return 0; 
    
}