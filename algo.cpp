#include <iostream>
#include <set>
#include <map>
#include <string>

using namespace std;

int main() {
    int no_of_transactions, friends;
    
    // Input validation for initial values
    if (!(cin >> no_of_transactions >> friends)) {
        cout << "Invalid input for transactions or friends" << endl;
        return 1;
    }
    
    if (friends < 2) {
        cout << "Need at least 2 friends to make transactions" << endl;
        return 1;
    }
    
    if (no_of_transactions < 1) {
        cout << "Need at least 1 transaction" << endl;
        return 1;
    }

    string x, y;
    int amount;
    map<string, int> net;
    int original_transactions = no_of_transactions;

    while (no_of_transactions--) {
        if (!(cin >> x >> y >> amount)) {
            cout << "Invalid input for transaction details" << endl;
            return 1;
        }
        
        if (amount <= 0) {
            cout << "Amount must be positive" << endl;
            continue;
        }
        
        if (x == y) {
            cout << "Sender and receiver cannot be the same person" << endl;
            continue;
        }

        // Initialize if person not in map
        if (net.count(x) == 0) {
            net[x] = 0;
        }
        if (net.count(y) == 0) {
            net[y] = 0;
        }

        // Update balances
        net[x] -= amount;
        net[y] += amount;
    }

    // Create sorted set of balances
    multiset<pair<int, string>> m;
    for (const auto& p : net) {
        string person = p.first;
        int amount = p.second;

        if (amount != 0) {
            m.insert(make_pair(amount, person));
        }
    }

    // Settlement process
    int settlement_count = 0;
    cout << "\nSettlement Transactions:" << endl;
    cout << "----------------------" << endl;
    
    while (!m.empty()) {
        auto low = m.begin();
        auto high = prev(m.end());

        int debit = low->first;
        string debit_person = low->second;

        int credit = high->first;
        string credit_person = high->second;

        m.erase(low);
        m.erase(high);

        int settlement_amount = min(-debit, credit);
        debit += settlement_amount;
        credit -= settlement_amount;

        cout << debit_person << " will pay " << settlement_amount << " to " << credit_person << endl;

        if (debit != 0) {
            m.insert(make_pair(debit, debit_person));
        }
        if (credit != 0) {
            m.insert(make_pair(credit, credit_person));
        }

        settlement_count++;
    }

    // Final statistics
    cout << "\nTransaction Summary:" << endl;
    cout << "-------------------" << endl;
    cout << "Original transactions: " << original_transactions << endl;
    cout << "Optimized settlements: " << settlement_count << endl;
    cout << "Reduction in transactions: " << 
            original_transactions - settlement_count << " (" << 
            ((float)(original_transactions - settlement_count) / original_transactions * 100) << 
            "%)" << endl;

    return 0;
}