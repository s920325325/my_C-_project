#include <bits/stdc++.h>
#include <windows.h>
using namespace std;

const int max_name_length = 20;

class mynumber {
  private:
    int number;
    int start = 1;
    int end = 100;
    int guess_time = 0;

  public:  
    mynumber(int start = 1, int end = 100) {
        std::random_device rd;
        std::mt19937 generator(rd());        
        std::uniform_int_distribution<int> distribution(start, end);
        int randomInt = distribution(generator);
        // std::cout << "Random number between " << start << " to " << end << " is generated! : " << randomInt << std::endl;
        std::cout << "Random number between " << start << " to " << end << " is generated!" << std::endl;
        this->number = randomInt;
    }
    int get_random_num(int start, int end) {
        std::random_device rd;
        std::mt19937 generator(rd());        
        std::uniform_int_distribution<int> distribution(start, end);
        int randomInt = distribution(generator);
        // std::cout << "Random number between " << start << " to " << end << " is generated! : " << randomInt << std::endl;
        return randomInt;
    }

    bool show_demo(){
        int random_num, g_time = 0;
        unordered_set<int> gen_num;

        cout << "Answer is " << this->number << endl;
        set_guess_time(g_time);
        do{
            Sleep(200);
            while(gen_num.find(random_num) != gen_num.end()){
                random_num = get_random_num(get_range()[0], get_range()[1]);
                cout<< "Random number generated: " << random_num << endl;
                Sleep(200);
            }
            cout<<endl;
            gen_num.insert(random_num);
            random_num = get_random_num(get_range()[0], get_range()[1]);
            cout << "Guessing: " << random_num << endl;
            gen_num;
            g_time++;
            if(guess(random_num, to_string(random_num))) {
                set_guess_time(g_time);
                cout << "total attempt: " << get_guess_time() << endl;
                return true;
            }
        } while (random_num != number);
        return false;
        
        
    }

    int get_guess_time() {
        return this->guess_time;
    }
    void set_guess_time(int guess_time) {
        this->guess_time = guess_time;
    }

    int get_number() {
        return this->number;
    }
    void set_number(int number) {
        this->number = number;
    }
    void set_range(int start, int end) {
        while(true){
            if(start <= end) {
                this->start = start;
                this->end = end;
                set_number(get_random_num(start, end));
                cout << "range set!" << endl;
                cout << this->number << endl;
                break;
            }else{
                std::cout << "Start number should be less than end number!" << std::endl;
                cout << "Enter start and end number again: ";
                std::cin >> start >> end;
            }
        }
    }

    array<int,2> get_range(){
        return {this->start, this->end};
    }
    
    bool guess(int guess_number, string str_guess_number) {
        try{
            
            if(str_guess_number == "00") {
                cout << "The answer is " << this->number << endl;
                return false;
            }

            if(guess_number >= this->get_range()[0] && guess_number <= this->get_range()[1]) {
                if(guess_number == this->number) {
                    cout << "You got it! the answer is " << this->number << "" << endl;
                    return true;
                }else if(this->get_range()[0] == this->get_range()[1]){
                    cout << "Almost got it!" << endl;

                } else if(guess_number < this->number) {
                    cout << "Too small!, ";
                    if(guess_number < this->get_range()[0]) {

                        cout << "Range: " << this->get_range()[0] << " to " << this->get_range()[1] << endl;
                        return false;
                    }
                    this->start = guess_number+1;
                    cout << "Range: " << this->get_range()[0] << " to " << this->get_range()[1] << endl;
                    return false;
                } else {
                    cout << "Too big!, ";
                    if(guess_number > this->get_range()[1]) {

                        cout << "Range: " << this->get_range()[0] << " to " << this->get_range()[1] << endl;
                        return false;
                    }
                    this->end = guess_number-1;
                    cout << "Range: " << this->get_range()[0] << " to " << this->get_range()[1] << endl;
                    return false;
                }
            }else{
                cout << "Out of range!" << endl;
                cout << "Range: " << this->get_range()[0] << " to " << this->get_range()[1] << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                return false;
            } // end of if
            return false;
        }catch(exception e){ // catch exception
            cout << "Exception caught: " << e.what() << endl;
            cout << "try again!" << endl;
            return false;
        } // end of catch
    } // end of guess
};


class player{
    private:
        string name = "Guest";
        int mode;
    public:
        player(){
            change_name();
        }

    void change_name() {
        cout << "Hello " << get_name() << ", what's your name?: " << endl;
        cout << "Press enter if no instruction is given" << endl;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Enter your name: , or press enter with name Guest" << endl;         
        // cin.ignore(numeric_limits<streamsize>::max(), '\n');  
        char ch;
        string new_name;
        // get user input
        while (cin.get(ch) && ch != '\n') {
            new_name += ch; // Append character to new_name
        }

        //process name
        if (new_name.empty() || new_name == "\\n") {
            set_name("Guest");
            cout << "Welcome " << get_name() << "!" << endl;
        } else {
            if (get_name() == new_name) {
                cout << "Your name is still " << get_name() << "." << endl;
            } else {
                set_name(new_name);
                cout << "Welcome " << get_name() << "!" << endl;
            }
        }     
        cout << "Press enter to continue..." << endl;
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); //clear buffer
        return;
        // cin.ignore();
                  

    }


        // Getters and Setters: mode
        int get_mode(){
            return this->mode;
        }
        void set_mode(int mode){
            this->mode = mode;
        }
        void set_name(string name){
            this->name = name;
        }
        string get_name(){
            return this->name;
        }

        void choose_mode(){
            while(true){
                cout << "Hello " << get_name() << ", " << endl;
                cout << "Choose mode: " << endl;
                cout << "1. Casual mode( default: number between 1 and 100 )" << endl;
                cout << "2. Custom mode( set your own range)" << endl;
                cout << "3. Demo" << endl;
                cout << "4. Change name" << endl;
                cout << "5. Exit" << endl;
                int mode;
                cin >> mode;
                if(mode > 0 && mode < 6) {
                    set_mode(mode);
                    break;
                }else {
                    cout << "Invalid mode!, try again " << endl;
                }
            }// end of while loop
        }// end of choose mode

        void mode_1(mynumber game){
            cout << "Enter guess number: 00 to show answer " << endl;
            string ans ;
            while(true) {
                cin >> ans;
                if(game.guess(stoi(ans), ans)) {
                    break;
                }
            }
        }
        void mode_2(mynumber game){
            // Setting range
            int start, end;
            cout << "Enter start and end number: "<< endl << "Start: ";
            cin >> start ;
            cout << "End: ";
            cin >> end;
            cout << endl <<"a random number between " << start << " and " << end << " is generated!" << endl;            
            game.set_range(start, end);
            mode_1(game);

        }
};


int main() {
    // TODO: implement the guessing game

    // Mode 1 finished
    // Starting mode 2
    player p;
    do{
        p.choose_mode();
        cout<< p.get_mode() << endl;

        if(p.get_mode() > 0 && p.get_mode() < 4) {
            mynumber game;
            switch(p.get_mode()){           
            case 1:
                p.mode_1(game);
                break;

            case 2:
                p.mode_2(game);
                break;

            case 3:
                game.show_demo();        
                break;
            default:
                cout << "invalid mode! " << endl;
                continue;  
            } // end of switch          
        } else if(p.get_mode() == 4) {
                p.change_name();  

        } else if(p.get_mode() == 5){
            cout << "bye! see you next time! " << p.get_name() << endl;
        } else{
            cout << "invalid mode! " << endl;
        }  
 
    } while( p.get_mode() != 5);
        


    return 0;
}