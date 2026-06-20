#pragma once

#include <QMap>
#include <QSet>
#include <QString>
#include <QStringList>
#include <QPair>
#include <QList>

class PersonGraph {
public:
    void addPerson(const QString& name) {
        if (!graph_.contains(name)) {
            graph_[name] = QSet<QString>();
        }
    }

    void addFriendship(const QString& a, const QString& b) {
        addPerson(a);
        addPerson(b);

        graph_[a].insert(b);
        graph_[b].insert(a);
    }

    QStringList people() const {
        QStringList result = graph_.keys();
        result.sort();
        return result;
    }

    QStringList friendsOf(const QString& name) const {
        QStringList result;

        if (!graph_.contains(name)) return result;

        for (const QString& f : graph_.value(name)) {
            result << f;
        }

        result.sort();
        return result;
    }

    QStringList recommendationsFor(const QString& name) const {
        QStringList result;

        if (!graph_.contains(name)) return result;

        QSet<QString> directFriends = graph_.value(name);
        QSet<QString> recommended;

        for (const QString& friendName : directFriends) {
            QSet<QString> friendsOfFriend = graph_.value(friendName);

            for (const QString& candidate : friendsOfFriend) {
                if (candidate != name && !directFriends.contains(candidate)) {
                    recommended.insert(candidate);
                }
            }
        }

        for (const QString& r : recommended) {
            result << r;
        }

        result.sort();
        return result;
    }

    QList<QPair<QString, QString>> edges() const {
        QList<QPair<QString, QString>> result;
        QSet<QString> added;

        for (const QString& a : graph_.keys()) {
            for (const QString& b : graph_.value(a)) {
                QString key1 = a + "-" + b;
                QString key2 = b + "-" + a;

                if (!added.contains(key1) && !added.contains(key2)) {
                    result.append(qMakePair(a, b));
                    added.insert(key1);
                }
            }
        }

        return result;
    }

private:
    QMap<QString, QSet<QString>> graph_;
};
