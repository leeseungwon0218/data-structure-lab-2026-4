#pragma once

#include <QWidget>
#include <QPainter>
#include <QMouseEvent>
#include <QMap>
#include <QPointF>
#include <functional>
#include "PersonGraph.h"

class GraphWidget : public QWidget {
public:
    GraphWidget(QWidget* parent = nullptr) : QWidget(parent) {
        setMinimumSize(650, 600);
        setStyleSheet("background:#0d1117;");
    }

    void setGraph(const PersonGraph* graph) {
        graph_ = graph;
        update();
    }

    void setPositions(const QMap<QString, QPointF>& positions) {
        positions_ = positions;
        update();
    }

    void setSelectedPerson(const QString& name) {
        selected_ = name;
        update();
    }

    void onPersonClicked(std::function<void(QString)> callback) {
        callback_ = callback;
    }

protected:
    void paintEvent(QPaintEvent*) override {
        QPainter p(this);
        p.setRenderHint(QPainter::Antialiasing);

        p.fillRect(rect(), QColor("#0d1117"));

        p.setPen(QColor("white"));
        QFont titleFont = p.font();
        titleFont.setPointSize(18);
        titleFont.setBold(true);
        p.setFont(titleFont);
        p.drawText(QRect(0, 15, width(), 40), Qt::AlignCenter, "SNS 친구 관계 그래프");

        if (!graph_) return;

        for (const auto& edge : graph_->edges()) {
            QString a = edge.first;
            QString b = edge.second;

            QPoint pa = posOf(a);
            QPoint pb = posOf(b);

            bool highlight = false;

            if (!selected_.isEmpty()) {
                QStringList friends = graph_->friendsOf(selected_);
                if ((a == selected_ && friends.contains(b)) ||
                    (b == selected_ && friends.contains(a))) {
                    highlight = true;
                }
            }

            if (highlight) {
                p.setPen(QPen(QColor("#facc15"), 4));
            } else {
                p.setPen(QPen(QColor(180, 180, 180, 90), 2));
            }

            p.drawLine(pa, pb);
        }

        for (const QString& name : graph_->people()) {
            QPoint c = posOf(name);
            bool selected = (name == selected_);
            int radius = selected ? 34 : 28;

            if (selected) {
                p.setBrush(QColor(79, 70, 229, 100));
                p.setPen(Qt::NoPen);
                p.drawEllipse(c, radius + 12, radius + 12);
            }

            p.setBrush(selected ? QColor("#4f46e5") : QColor("#2563eb"));
            p.setPen(QPen(QColor("white"), 2));
            p.drawEllipse(c, radius, radius);

            p.setPen(QColor("white"));
            QFont nameFont = p.font();
            nameFont.setPointSize(11);
            nameFont.setBold(true);
            p.setFont(nameFont);

            p.drawText(QRect(c.x() - 45, c.y() - 12, 90, 24),
                       Qt::AlignCenter, name);
        }

        p.setPen(QColor("#cbd5e1"));
        QFont hintFont = p.font();
        hintFont.setPointSize(11);
        hintFont.setBold(false);
        p.setFont(hintFont);

        p.drawText(QRect(0, height() - 45, width(), 30),
                   Qt::AlignCenter,
                   "사람 노드를 클릭하면 직접 친구와 추천 친구가 표시됩니다.");
    }

    void mousePressEvent(QMouseEvent* event) override {
        if (!graph_) return;

        for (const QString& name : graph_->people()) {
            QPoint c = posOf(name);

            int dx = event->pos().x() - c.x();
            int dy = event->pos().y() - c.y();

            if (dx * dx + dy * dy <= 36 * 36) {
                if (callback_) callback_(name);
                return;
            }
        }
    }

private:
    QPoint posOf(const QString& name) const {
        QPointF n = positions_.value(name, QPointF(0.5, 0.5));

        int marginX = 80;
        int marginY = 90;

        int x = marginX + int(n.x() * (width() - marginX * 2));
        int y = marginY + int(n.y() * (height() - marginY * 2));

        return QPoint(x, y);
    }

    const PersonGraph* graph_ = nullptr;
    QMap<QString, QPointF> positions_;
    QString selected_;
    std::function<void(QString)> callback_;
};
