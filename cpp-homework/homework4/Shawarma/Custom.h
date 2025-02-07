#include <vector>
#include <map>
#include <string>
#include <iostream>
#include <algorithm>

using namespace std;

class Comment {
public:
    int version;
    double food_rating;
    double service_rating;
    double environment_rating;
    string timestamp;

    Comment(int version, double food_rating, double service_rating, double environment_rating, string timestamp) : version(version), food_rating(food_rating), service_rating(service_rating), environment_rating(environment_rating), timestamp(timestamp) {}
};

class Custom {
public:
    int custom_id; // 用户id
    // 用户评论
    vector<Comment *> comments;

    // 最新评分
    double food_rating;
    double service_rating;
    double environment_rating;

    Custom(int custom_id, double food_rating, double service_rating, double environment_rating) : custom_id(custom_id), food_rating(food_rating), service_rating(service_rating), environment_rating(environment_rating) {}
};

class CommentsSystem {
private:
    map<int, Custom *> comments;

public:
    void insertComment(int custom_id, double food_rating, double service_rating, double environment_rating, string timestamp) {
        Custom *new_custom = new Custom(custom_id, food_rating, service_rating, environment_rating);
        new_custom->comments.push_back(new Comment(1, food_rating, service_rating, environment_rating, timestamp));
        comments[custom_id] = new_custom;
        cout << "Review inserted successfully" << endl;
    }

    void modifyComment(int custom_id, string dimension, double new_rating, string timestamp) {
        if (comments.find(custom_id) == comments.end()) {
            cout << "Customer ID not found, modification failed" << endl;
            return;
        }

        Custom *curr_custom = comments[custom_id];
        int version = curr_custom->comments.size() + 1;
        if (dimension == "food")
            curr_custom->food_rating = new_rating;
        else if (dimension == "service")
            curr_custom->service_rating = new_rating;
        else if (dimension == "environment")
            curr_custom->environment_rating = new_rating;

        curr_custom->comments.push_back(new Comment(version, curr_custom->food_rating, curr_custom->service_rating, curr_custom->environment_rating, timestamp));

        cout << "Modification successful" << endl;
    }

    void deleteCustom(int custom_id) {
        if (comments.find(custom_id) == comments.end()) {
            cout << "Customer ID not found, deletion failed" << endl;
            return;
        }

        comments.erase(custom_id);
        cout << "Deletion successful" << endl;
    }

    void history(int custom_id, string dimension) {
        if (comments.find(custom_id) == comments.end())
            return;

        Custom *curr_custom = comments[custom_id];

        cout << "History:" << endl;
        for (auto it = curr_custom->comments.rbegin(); it != curr_custom->comments.rend(); ++it) {
            Comment *temp = *it;
            cout << "Version " << temp->version << ":";
            if (dimension.empty() || dimension == "food")
                cout << " Food Rating " << temp->food_rating;
            if (dimension.empty() || dimension == "service")
                cout << " Service Rating " << temp->service_rating;
            if (dimension.empty() || dimension == "environment")
                cout << " Environment Rating " << temp->environment_rating;
            cout << " Timestamp " << temp->timestamp << endl;
        }
    }

    void display(string dimension) {
        vector<pair<int, Comment *>> latestComments;

        for (auto it : comments) {
            Comment *latest_comment = it.second->comments.back();
            latestComments.push_back({it.first, latest_comment});
        }

        sort(latestComments.begin(), latestComments.end(), [](const pair<int, Comment *> a, const pair<int, Comment *> b) {
            return a.second->timestamp > b.second->timestamp;
        });

        for (auto latest_comment : latestComments) {
            cout << "Customer ID " << latest_comment.first;
            if (dimension.empty() || dimension == "food")
                cout << " Food Rating " << latest_comment.second->food_rating;
            if (dimension.empty() || dimension == "service")
                cout << " Service Rating " << latest_comment.second->service_rating;
            if (dimension.empty() || dimension == "environment")
                cout << " Environment Rating " << latest_comment.second->environment_rating;
            cout << " Timestamp " << latest_comment.second->timestamp << endl;
        }
    }

    void range_query(double food_low, double food_high, double service_low, double service_high, double environment_low, double environment_high) {
        vector<pair<int, Comment *>> latestComments;

        for (auto it : comments) {
            Comment *latest_comment = it.second->comments.back();
            if (latest_comment->food_rating >= food_low && latest_comment->food_rating <= food_high && latest_comment->service_rating >= service_low && latest_comment->service_rating <= service_high && latest_comment->environment_rating >= environment_low && latest_comment->environment_rating <= environment_high) {
                latestComments.push_back({it.first, latest_comment});
            }
        }

        sort(latestComments.begin(), latestComments.end(), [](const pair<int, Comment *> a, const pair<int, Comment *> b) {
            return a.first > b.first;
        });

        for (auto latest_comment : latestComments) {
            cout << "Customer ID " << latest_comment.first << " Food Rating " << latest_comment.second->food_rating << " Service Rating " << latest_comment.second->service_rating << " Environment Rating " << latest_comment.second->environment_rating << " Timestamp " << latest_comment.second->timestamp << endl;
        }
    }
};
