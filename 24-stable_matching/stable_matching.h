#include <vector>
#include <string>
#include <map>
#include <algorithm>
#include <iostream>

class Stable_Matching {
    public:

        // Constructor
        Stable_Matching(int marriages) : marriages(marriages),
                                         last_match(marriages, 0),
                                         matched_men(marriages, false), 
                                         matched_women(marriages, false), 
                                         current_men_matches(marriages, -1), 
                                         current_women_matches(marriages, -1) { };

        // Setters
        void setMen(vector<string>& men) { this->men = men; }
        void setWomen(vector<string>& women) { this->women = women; }
        void setMenPreferences(vector<vector<int>>& men_preferences) { this->men_preferences = men_preferences; }
        void setWomenPreferences(vector<vector<int>>& women_preferences) { this->women_preferences = women_preferences; }

        // Functions
        map<string, string> findStableMarriage() {

            // initialize map for result
            map<string, string> matchings;

            // are settings valid?
            if ( this->marriages != this->men.size()
                || this->men.size() != this->women.size() 
                || this->men_preferences.size() != this->men.size() 
                || this->women_preferences.size() != this->women.size()
                || this->men_preferences[0].size() != this->women.size()
                || this->women_preferences[0].size() != this->men.size()) {
                    cout << "Wrong settings" << endl;
                    return matchings;
            } 

            // start gale-shapley algorithm
            int matches = this->men.size();
            while (find(this->matched_men.begin(), this->matched_men.end(), false) != this->matched_men.end()) {
                for (int i = 0; i < matches; i++) {
                    if (!this->matched_men[i]) {
                        findMatchForMen(i);
                    }
                }
            } 

            // combine results in map
            cout << "All men matched!" << endl;
            
            /* TODO */

            return matchings;
        }

    private:

        // Private Functions
        void findMatchForMen(int index) {

            // take next women until not matched
            while (!this->matched_men[index]) {

                // find the position of the women
                this->last_match[index]++;
                vector<int>::iterator iter = find(this->men_preferences[index].begin(), this->men_preferences[index].end(), this->last_match[index]);
                int women_pos = iter - this->men_preferences[index].begin();

                if (this->matched_women[women_pos]) {

                    // always check if women doesn't prefer the man over the current one
                    cout << this->men[index] << "! " << this->women[women_pos] << " is already married" << endl;
                    int current_rank = this->women_preferences[women_pos][this->current_women_matches[women_pos]];
                    int new_rank = this->women_preferences[women_pos][index];

                    if (new_rank < current_rank) {
                        vector<int>::iterator iter = find(this->women_preferences[women_pos].begin(), this->women_preferences[women_pos].end(), current_rank);
                        int man_pos = iter - this->women_preferences[women_pos].begin();

                        cout << this->women[women_pos] << " breaks with " << this->men[man_pos] << endl;
                        cout << this->men[index] << " marries with " << this->women[women_pos] << endl;
                        this->matched_men[index] = true;
                        this->current_men_matches[index] = women_pos;
                        this->matched_men[man_pos] = false;
                        this->current_men_matches[man_pos] = -1;

                        this->current_women_matches[women_pos] = index;
                    }
                    else {
                        cout << this->women[women_pos] << "stays with her current man" << endl;
                    }

                }
                else {
                    cout << this->men[index] << " marries with " << this->women[women_pos] << endl;
                    this->matched_men[index] = true;
                    this->matched_women[women_pos] = true;
                    this->current_men_matches[index] = women_pos;
                    this->current_women_matches[women_pos] = index;
                }
            }
        }

        // Fields
        int marriages;
        vector<string> men;
        vector<string> women;
        vector<vector<int>> men_preferences;
        vector<vector<int>> women_preferences;

        vector<int> last_match;

        vector<bool> matched_men;
        vector<bool> matched_women;

        vector<int> current_men_matches;
        vector<int> current_women_matches;
};
