#include <iostream>
#include <string>
#include <curl/curl.h>
#include <vector>
#include "JsonResponse.h"
#include<cstdlib>

using namespace std;

 size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* output) {
    size_t total_size = size * nmemb;
    output->append((char*)contents, total_size);
    return total_size;
}
     
struct Result{
string data;
CURLcode code;

    Result(string data = "", CURLcode code = CURLE_OK){
	    this->data = data;
    	code =code; 
    }
};

void clearScreen(){
	system("cls");
	
}

class CurlApi{
	
	CURL* curl;
	Result* result;
    

	ApiResponse parseJson(string response){	
       ApiResponse data = parse_json(response);
         return data; 
	}
	public:
	CurlApi(){
		curl = nullptr;
		result = nullptr;
	}
	
	void initilize_Curl(){
		
    curl = curl_easy_init();
	}
	
	void clear_Curl(){
		
     curl_easy_cleanup(curl);	
        delete result;
   	    result= nullptr;
	
	}
	
	CURL* getCurl( ){ 
	return curl;
	}
	
    void makeApiReuest( CURL* curl,std::string& city){
	
	if(curl){
		curl_easy_reset(curl);
		char* encoded_city = curl_easy_escape(curl,city.c_str(), city.length());
		
		string url =  "https://api.openweathermap.org/data/2.5/weather?q=" +
		             string(encoded_city) + 
					 "&appid=2b2e95bbad630598c4c6f2c70486a030&units=metric";
					 		 
        Result* localResult = new Result();
		curl_free(encoded_city);
		curl_easy_setopt(curl, CURLOPT_URL, url.c_str()); ///( handle, option , parameters)
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback); //(handle, option
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &localResult->data);
        
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L); //(handle , option for to disbable the verifyPeer , 0L if want to disabled otherwise 1L by default its 1L becasue the curl libraray it slef check the CA ( certificate Authority ) if he check that trustbable or not  ) 
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);

	    localResult->code = curl_easy_perform(curl);
	    if(localResult->code != CURLE_OK) {
            cerr << "curl_easy_perform() failed: " << curl_easy_strerror(localResult->code) << endl;
		}
		
        result = localResult;
	}
	
	
   }
	
	Result* getResult() {
		return result;
	}
	
   void printResponse(){
	
	if (result->code != CURLE_OK) {
            cerr << "CURL Error: " << curl_easy_strerror(result->code) << endl;
    }else {
	
	ApiResponse data = parseJson(result->data); 
	   	
	cout << "Temperature (approx): " << data.main.temp << "°C" ;
    cout << "   Country " << data.sys.country << endl;
	
	}
}	
	
};

struct ListNode{
	
	string key, value;
	ListNode* next;
	
	ListNode(string key, string value){
		
		this->key = key;
		this->value = value;
		next = nullptr;
	}
};

class LinkedList{
	ListNode* head ;
	CurlApi api;
	public:
		
		LinkedList(){
			head = nullptr;
		}
		
		void insert(string key, string value){
			if(!head){
				head = new ListNode(key, value);
			}else {
				ListNode* current= head;
				while(current->next != nullptr){
					current = current->next;
				}
				
				current->next = new ListNode(key,value);
			}
		
		}
		
		void insert( string value){
			
			 string key = "";
			if(!head){
				head = new ListNode(key, value);
			}else {
				ListNode* current= head;
				while(current->next != nullptr){
					current = current->next;
				}
				
				current->next = new ListNode(key,value);
			}
			
		}
		void print(string prefix){
			
			api.initilize_Curl();
			if(head != nullptr){
				
			ListNode * current = head;
				while(current != nullptr){
					
				CURL* curl = api.getCurl();
				
					if(current->key== prefix){
						api.makeApiReuest(curl,current->value);
				
						cout<< " - "<<current->value<<"\t\t:\t" ;
						api.printResponse();
					}
					current = current->next;
				}
				
				
			}
			
		}
		
		bool hasPrefix(string prefix){
			ListNode* current = head;
			
			while(current != nullptr){
				
				if(current->key  == prefix){
					return true;
				}
				
				current = current->next;
			}
			
			return false;
		}
		
		void print(){
			ListNode* current = head;
			while(current != NULL){
				cout<< " - "<<current->value <<endl;
				current = current->next;
			}
			
			delete current;
			current  = nullptr; 
		}
		
		void deleteNode(string value){
			
			if(head != NULL){
				
				
			if(head->value == value){
				ListNode* temp =head;
				head = head->next;
				
				delete temp;
				temp= NULL;
				return;
			}
			ListNode* current = head;
			
			while(current != NULL){
				
				if(current->next->value == value ){
					
					if(current->next->next == NULL){
					
			    		ListNode* temp = current->next;
		    			current->next = NULL;
	    				delete temp;
    					temp = NULL;
    					break;
    					return ;					
					}
					ListNode* next = current->next->next;
					
					delete current->next;
					current->next  = next;
					return ;
				}		
			
				current= current->next;
			   }
				
			   if(current == NULL){
					cout<<"Not Present In the History List.\n";
				}
	
			
				
			}else {
				cout<<"List is Empty.\n";
				return ;
			}
			   
	   
	   }
	   
	   void deleteAll(){
	   	
	   	if(head != NULL){
	   		
	   	     ListNode* current = head;
	   		
			  while(current != NULL){
	   			
	   			ListNode* next= current->next;
	   			ListNode* temp = current;
	   			delete temp;
	   			temp = NULL;
	   			current = next;		
	   			
			  }
			  head = nullptr;
			 
		   }else {
		   	cout<<"List Is Empty.\n";
		   	return ;
		   }
		   
	   }

		
};


class HashMap{
	
	LinkedList* buckets;
	int capacity;
	
	int hash(string key){
		int hash = 0;
	
		for (char c:key){
			hash = hash * 31 +c;
		}
		
		return hash % capacity;
	}
	public:
		
		HashMap(int capacity = 2000){
			
			this->capacity  = capacity;
			buckets = new LinkedList[capacity];
		}
		
		void insert(string key , string value){
			int index = hash(key);
			
			buckets[index].insert(key, value);
		
		}
		
		
		void printAutoComplete(string prefix){
			int index =hash(prefix);
			cout<<" Suggestion  for " <<prefix <<"':\n";
			
			buckets[index].print(prefix);
		}
};



class AutoCompleteSystem{
	
	HashMap preixMap;
	LinkedList searchHistory;
	void buildPrefixMap( string cities[], int count){
		
		for(int i =0 ; i<count ; i++){
			string city = cities[i];
			
			for(int inner = 1;  inner <= city.length(); inner++){
				string prefix = city.substr(0,inner);
				preixMap.insert(prefix, city);
			}
		}
	}
     public:
     	
     	AutoCompleteSystem( string cities[], int count){
     		buildPrefixMap(cities, count);
		 }
		 
		 void querry(string prefix){
		 	preixMap.printAutoComplete(prefix);
		 }
		 void add_to_History(string search){
		 	
		 	searchHistory.insert(search);
		 }
		 
		 void delete_to_History(string value){
		 	searchHistory.deleteNode(value);
		 	
		 }
		 void printHistory(){
		 	searchHistory.print();
		 }
		 
		 void delete_All_history(){
		 	searchHistory.deleteAll();
		 }
};




int main() {
     string cities[] = {
    // Major world cities
    "New York", "London", "Tokyo", "Paris", "Dubai", 
    "Singapore", "Bangkok", "Hong Kong", "Los Angeles",
    "Chicago", "Toronto", "Sydney", "Melbourne", "Berlin",
    "Rome", "Madrid", "Moscow", "Seoul", "Beijing", "Shanghai",
    
    // US Cities
    "Houston", "Phoenix", "Philadelphia", "San Antonio", "San Diego",
    "Dallas", "San Jose", "Austin", "Jacksonville", "Fort Worth",
    "Columbus", "Charlotte", "San Francisco", "Indianapolis",
    "Seattle", "Denver", "Washington", "Boston", "El Paso", "Detroit",
    
    // European Cities
    "Amsterdam", "Brussels", "Vienna", "Prague", "Copenhagen",
    "Dublin", "Helsinki", "Athens", "Budapest", "Oslo",
    "Warsaw", "Lisbon", "Bucharest", "Stockholm", "Zurich",
    "Istanbul", "Milan", "Barcelona", "Munich", "Manchester",
    
    // Asian Cities
    "Delhi", "Mumbai", "Bangalore", "Jakarta", "Manila",
    "Ho Chi Minh City", "Kuala Lumpur", "Taipei", "Osaka", "Kyoto",
    "Dhaka", "Karachi", "Lahore", "Colombo", "Hanoi",
    
    // Middle Eastern Cities
    "Riyadh", "Doha", "Abu Dhabi", "Tel Aviv", "Jerusalem",
    "Cairo", "Alexandria", "Jeddah", "Ankara", "Beirut",
    
    // African Cities
    "Cape Town", "Johannesburg", "Nairobi", "Lagos", "Accra",
    "Casablanca", "Addis Ababa", "Khartoum", "Dar es Salaam", "Tunis",
    
    // South American Cities
    "Rio de Janeiro", "São Paulo", "Buenos Aires", "Lima", "Bogotá",
    "Santiago", "Caracas", "Montevideo", "Quito", "La Paz",
    
    // Australian/Oceania
    "Brisbane", "Perth", "Adelaide", "Auckland", "Wellington",
    "Christchurch", "Honolulu", "Port Moresby", "Suva",
    
    // Indian Cities (more detailed)
    "Kolkata", "Chennai", "Hyderabad", "Pune", "Ahmedabad",
    "Jaipur", "Surat", "Lucknow", "Kanpur", "Nagpur",
    "Visakhapatnam", "Patna", "Bhopal", "Ludhiana", "Agra",
    
    // Canadian Cities
    "Montreal", "Vancouver", "Calgary", "Ottawa", "Edmonton",
    "Winnipeg", "Quebec City", "Hamilton", "Halifax",
    
    // Additional International
    "Baku", "Yerevan", "Tbilisi", "Almaty", "Astana",
    "Kiev", "Minsk", "Belgrade", "Sofia", "Zagreb"
};

    int totalCities = sizeof(cities)/sizeof(cities[0]);
    char input;
    
    string userInput;
    AutoCompleteSystem ac(cities, totalCities); 	
    
    
    do{
    	clearScreen();
		    
    cout<<"...................................\n";	
    cout<<" Weather Forecasting\n";
    cout<<" 1- Check Weather By City\n";
    cout<<" 2- History\n";
    cout<<" 3- Exit\n ";
    
    cout<<".....................................\n";
    cout<<"Select Your Option.\n";
    cin >> input;
    switch(input){
    	    	
    	case '1' :{
    		cout<<"Enter City Prefix Must be Capitalized.\n";
			cin >>userInput;
			ac.add_to_History(userInput);
			cin.ignore();
			ac.querry(userInput);
			break;
		}
		
		
		case '2':{
			
			char searchChoice;
			do{
				
			cout<<"History Manager .\n";
			cout<<"1 - See History.\n";
			cout<<"2 - Delete Specific.\n";
			cout<<"3 - Delete All.\n";
			cout<<"4 - Back.\n";
			cout<<" Enter Your Choice .\n";
			cin >>searchChoice;
			
		switch(searchChoice){
			
				case '1': {
					
					cout<<"--- Recent Searches.\n";
					ac.printHistory();
					break;
				}
				
				case '2': {
					
					string deletevalue;
					cout<<"Enter History \n";
					cin >>deletevalue;
					ac.delete_to_History(deletevalue);
					break;
				}
				
				case '3' :{
					
					ac.delete_All_history();
					break;
				}
				
				default :{
					
					cout<<"Invalid  Choice.\n";
					break;
				}
			}			
			
			} while(searchChoice != '4');
			
			break;
		}
		
		case '3': {
			
			cout<<"Thank You For Using Our Service.\n";
			break;
		}
		
		default :{
			
			cout<<"OOPs! Invalid Option.\n";
			break;
		}
		
		
	}
	
	cout<<"Press Any key To Continue.\n";
	cin.ignore();

	}while(input != '3');
    
    return 0;
}

