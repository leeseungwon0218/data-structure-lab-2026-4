#pragma once

#include <QMainWindow>
#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QListWidget>
#include <QTextEdit>
#include <QMap>
#include <QPointF>
#include "PersonGraph.h"
#include "GraphWidget.h"

class MainWindow : public QMainWindow {
public:
    MainWindow() {
        setWindowTitle("SNS 친구 추천 프로그램 - 그래프 자료구조");
        resize(1200, 700);

        buildGraph();
        buildPositions();
        buildUI();

        QString first = graph_.people().first();
        selectPerson(first);
    }

private:
    void buildGraph() {
        graph_.addFriendship("민수", "지훈");
        graph_.addFriendship("민수", "유진");
        graph_.addFriendship("지훈", "서연");
        graph_.addFriendship("지훈", "도윤");
        graph_.addFriendship("유진", "하늘");
        graph_.addFriendship("유진", "지민");
        graph_.addFriendship("서연", "나연");
        graph_.addFriendship("도윤", "현우");
        graph_.addFriendship("하늘", "태준");
        graph_.addFriendship("지민", "나연");
        graph_.addFriendship("현우", "태준");
    }

    void buildPositions() {
        positions_["민수"] = QPointF(0.50, 0.10);
        positions_["지훈"] = QPointF(0.25, 0.28);
        positions_["유진"] = QPointF(0.75, 0.28);
        positions_["서연"] = QPointF(0.12, 0.52);
        positions_["도윤"] = QPointF(0.38, 0.52);
        positions_["하늘"] = QPointF(0.62, 0.52);
        positions_["지민"] = QPointF(0.88, 0.52);
        positions_["나연"] = QPointF(0.25, 0.80);
        positions_["현우"] = QPointF(0.50, 0.82);
        positions_["태준"] = QPointF(0.75, 0.80);
    }

    void buildUI() {
        QWidget* central = new QWidget(this);
        setCentralWidget(central);

        QHBoxLayout* mainLayout = new QHBoxLayout(central);
        mainLayout->setContentsMargins(0, 0, 0, 0);
        mainLayout->setSpacing(0);

        graphWidget_ = new GraphWidget;
        graphWidget_->setGraph(&graph_);
        graphWidget_->setPositions(positions_);
        mainLayout->addWidget(graphWidget_, 3);

        QWidget* panel = new QWidget;
        panel->setMinimumWidth(380);
        panel->setStyleSheet("background:#252526; color:white;");

        QVBoxLayout* panelLayout = new QVBoxLayout(panel);
        panelLayout->setContentsMargins(18, 18, 18, 18);
        panelLayout->setSpacing(10);

        titleLabel_ = new QLabel("선택된 사람");
        titleLabel_->setStyleSheet("font-size:24px; font-weight:bold; color:white;");
        panelLayout->addWidget(titleLabel_);

        QLabel* infoLabel = new QLabel("왼쪽 그래프의 사람 노드를 클릭하거나 아래 목록에서 선택하세요.");
        infoLabel->setWordWrap(true);
        infoLabel->setStyleSheet("font-size:13px; color:#9ca3af;");
        panelLayout->addWidget(infoLabel);

        QLabel* listLabel = new QLabel("사람 목록");
        listLabel->setStyleSheet("font-size:16px; font-weight:bold; color:#93c5fd;");
        panelLayout->addWidget(listLabel);

        personList_ = new QListWidget;
        personList_->setStyleSheet(
            "QListWidget { background:#1f2937; color:white; border:1px solid #374151; font-size:15px; }"
            "QListWidget::item { padding:7px; }"
            "QListWidget::item:selected { background:#4f46e5; color:white; }"
        );

        for (const QString& name : graph_.people()) {
            personList_->addItem(name);
        }

        panelLayout->addWidget(personList_, 1);

        QLabel* friendLabel = new QLabel("직접 친구");
        friendLabel->setStyleSheet("font-size:16px; font-weight:bold; color:#22c55e;");
        panelLayout->addWidget(friendLabel);

        friendsText_ = new QTextEdit;
        friendsText_->setReadOnly(true);
        friendsText_->setStyleSheet("background:#111827; color:white; border:1px solid #374151; font-size:15px;");
        panelLayout->addWidget(friendsText_, 1);

        QLabel* recommendLabel = new QLabel("추천 친구");
        recommendLabel->setStyleSheet("font-size:16px; font-weight:bold; color:#facc15;");
        panelLayout->addWidget(recommendLabel);

        recommendText_ = new QTextEdit;
        recommendText_->setReadOnly(true);
        recommendText_->setStyleSheet("background:#111827; color:white; border:1px solid #374151; font-size:15px;");
        panelLayout->addWidget(recommendText_, 1);

        QLabel* explainLabel = new QLabel("그래프 설명");
        explainLabel->setStyleSheet("font-size:16px; font-weight:bold; color:#c084fc;");
        panelLayout->addWidget(explainLabel);

        explainText_ = new QTextEdit;
        explainText_->setReadOnly(true);
        explainText_->setStyleSheet("background:#111827; color:white; border:1px solid #374151; font-size:14px;");
        explainText_->setText(
            "정점(Vertex): 사람\n"
            "간선(Edge): 친구 관계\n"
            "그래프 종류: 무방향 그래프\n\n"
            "선택한 사람의 직접 친구를 찾고,\n"
            "그 친구들의 친구 중에서 아직 직접 친구가 아닌 사람을 추천합니다."
        );
        panelLayout->addWidget(explainText_, 1);

        mainLayout->addWidget(panel, 1);

        graphWidget_->onPersonClicked([this](QString name) {
            selectPerson(name);
        });

        connect(personList_, &QListWidget::itemClicked, this, [this](QListWidgetItem* item) {
            selectPerson(item->text());
        });
    }

    QString makeListText(const QStringList& list) {
        if (list.isEmpty()) return "없음";

        QString text;
        for (const QString& item : list) {
            text += "• " + item + "\n";
        }
        return text;
    }

    void selectPerson(const QString& name) {
        titleLabel_->setText("선택된 사람: " + name);

        friendsText_->setText(makeListText(graph_.friendsOf(name)));
        recommendText_->setText(makeListText(graph_.recommendationsFor(name)));

        graphWidget_->setSelectedPerson(name);

        QList<QListWidgetItem*> items = personList_->findItems(name, Qt::MatchExactly);
        if (!items.isEmpty()) {
            personList_->setCurrentItem(items.first());
        }
    }

private:
    PersonGraph graph_;
    QMap<QString, QPointF> positions_;

    GraphWidget* graphWidget_;
    QListWidget* personList_;
    QLabel* titleLabel_;
    QTextEdit* friendsText_;
    QTextEdit* recommendText_;
    QTextEdit* explainText_;
};
