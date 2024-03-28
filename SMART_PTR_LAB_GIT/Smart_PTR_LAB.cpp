
#include <memory>
#include <iostream>
#include <string>
#include <optional>

using namespace std;

struct FootballPlayer {
    string name;
    int num;
};

class FootballRoster {
private:
    struct Node { FootballPlayer player;
        shared_ptr<Node> next;
        Node(const FootballPlayer& player) : player(player), next(nullptr) {}
    };

    shared_ptr<Node> head;
    weak_ptr<Node> favoritenode;

public:
    void addPlayer(FootballPlayer player) { auto new_node = make_shared<Node>(player);
        if (!head) {
            head = new_node;
        } else {
            new_node->next = head;
            head = new_node;
        }
    }

    bool deletePlayer(string name) {
        if (!head) {
            return false;
        }

        if (head->player.name == name) {
            if (head == favoritenode.lock()) {
                favoritenode.reset();
            }
            head = head->next;
            return true;
        }

        auto current = head;
        shared_ptr<Node> prev = nullptr;
        while (current && current->player.name != name) {
            prev = current;
            current = current->next;
        }

        if (current && current->player.name == name) {
            if (current == favoritenode.lock()) {
                favoritenode.reset();
            }
            prev->next = current->next;
            return true;
        }

        return false;
    }

    bool setFavorite(string name) {
        if (!head) {return false;}
        auto current = head;
        while (current) {
            if (current->player.name == name) {
                favoritenode = current;
                return true;
            }
            current = current->next;
        }

        return false;
    }

    std::optional<FootballPlayer> getFavorite() const {
        if (favoritenode.expired()) {
            return nullopt;
        }
        return favoritenode.lock()->player;
    }
    void printPlayers() const {
        auto current = head;
        while (current) {
            cout << current->player.name << " #" << current->player.num << endl;
            current = current->next;
        }
    }
};


void favoritePlayer(const FootballRoster& roster) {
    auto fav = roster.getFavorite();
    if (fav) {
        cout << "Your favorite player is: " << fav->name << endl;
    } else {
        cout << "You don't have a favorite player." << endl;
    }
}

int main() {
    FootballPlayer fb3{ "Matthew Stafford", 9 };
    FootballPlayer fb2{ "Aaron Donald", 99 };
    FootballPlayer fb1{ "Jalen Ramsey", 5 };

    FootballRoster roster;

    roster.addPlayer(fb3);
    roster.addPlayer(fb2);
    roster.addPlayer(fb1);

    roster.printPlayers();
    roster.setFavorite("Aaron Donald");

    favoritePlayer(roster);

    roster.deletePlayer("Aaron Donald");
    favoritePlayer(roster);

    return 0;
}
