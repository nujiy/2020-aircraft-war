#include "gamebackground.h"
//目录
//    程序初始化函数
//        Space::Space(QWidget *parent=0);
//        void init();
//    槽函数
//        void Space::slt_newGame();
//        void Space::slt_playerDead();
//        void Space::slt_startGame();
//        void Space::slt_pauseGame();
//        void Space::slt_updata();
//        void Space::slt_menu();
//        void Space::slt_addscore(int score);
//    事件处理函数
//        void mouseDoubleClickEvent(QMouseEvent *event);
//    其他函数
//        void Space::enemys()；

//程序初始化
/****************************************************************************************************************************************/
GameBackground::GameBackground(QWidget *parent) : QGraphicsView(parent), boss(false),  gameStarted(false) {
    m_scene = new QGraphicsScene;
    m_scene->setSceneRect(0, 0, SCENEWIDTH, SCENEHEIGHT);
    setScene(m_scene);             //绑定view，此项目中为space，和scene

    //窗口显示属性设置
    setWindowFlags(Qt::FramelessWindowHint);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setCacheMode(QGraphicsView::CacheBackground);
    //将背景置于Cache中，加速渲染
    setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
    //设置QGraphicsView如何更新渲染画面
    setOptimizationFlags(QGraphicsView::DontClipPainter | QGraphicsView::DontSavePainterState);
    setRenderHint(QPainter::Antialiasing);

    QPixmap pix(SCENEWIDTH, SCENEHEIGHT);
    pix.load(background);
    //background在global.h中定义
    //const QString background = ":/image/background/background.jpeg";
    QPixmap temp = pix.scaled(SCENEWIDTH, SCENEHEIGHT, Qt::KeepAspectRatioByExpanding);
    setBackgroundBrush(temp);

    //绑定子弹与飞机VM
    std::shared_ptr<awmodel> m_M(std::make_shared<awmodel>());
    m_VM = std::make_shared<awviewmodel>();
	m_VM->SetModel(m_M);

    //m_timer=start(50);
    //使用m_timer数值定义屏幕刷新间隔
    //m_timer = new QTimer;
    //使用定时器刷新游戏界面
    //connect(m_timer, SIGNAL(timeout()), this, SLOT(slt_updata()));
    //菜单界面, 鼠标双击游戏界面发送信号
    connect(this, SIGNAL(sig_menu()), this, SLOT(slt_menu()));
    //绑定指令
    connect(this, SIGNAL(sig_start()), m_VM, SLOT(slt_start()));
    connect(this, SIGNAL(sig_pause()), m_VM, SLOT(slt_pause()));
    connect(this, SIGNAL(sig_keyinput(int kv, int en)), m_VM, SLOT(slt_keyinput(int kv, int en)));
    connect(m_VM, SIGNAL(sig_playerDead()), this, SLOT(slt_playerDead()));
    connect(m_VM, SIGNAL(sig_upScore(int)), this, SLOT(slt_upScore(int)));
    //connect(m_VM, SIGNAL(sig_createVO(&VisualObject)), this, SLOT(slt_createVO(&VisualObject)))
    init();
}

// void GameBackground::init() {
//     //初始化玩家飞机
//     m_scores = 0;
//     m_bloods = PLAYERPLANEBLOOD, m_bombs = 0, m_level = 1, m_step = 0;
//     //显示玩家飞机
//     QPixmaps t;
//     t.append(QPixmap(playerplane0));
//     t.append(QPixmap(playerplane1));
//     t.append(QPixmap(playerplane2));
//     t.append(QPixmap(playerplane3));
//     m_player = new Player(PLAYERPLANEBLOOD, PLAYERPLANESIZE, PLAYERPLANESIZE, PLAYERPLANESPEED, t, m_scene);
//     //QGraphicsItem::setFocus()
//     //功能：使得玩家飞机获取键盘焦点
//     m_player->setFocus();
// }

/* void GameBackground::CreateNPC()
{
    //生成普通NPC飞机
    if (m_level < 6)
    {
        GenerateNpc::NormalNpcs fishplanes = GenerateNpc::ncreator(m_level, scene());
        foreach (NormalNPC *f, fishplanes) {
            int z =  RandAlg::creat(6);
            if (z == 1) {
                int y = RandAlg::creat(SCENEHEIGHT / 2 - FISHSIZE);
                f->setPos(0, y);
            }
            else if (z == 2) {
                int y = RandAlg::creat(SCENEHEIGHT / 2 - FISHSIZE);
                f->setPos(SCENEWIDTH - FISHSIZE, y);
            }
            else {
                int x = RandAlg::creat(SCENEWIDTH - FISHSIZE);
                f->setPos(x, 0);
            }
            connect(f, SIGNAL(sig_score(int)), this, SLOT(slt_addscore(int)));
        }
    }
    //生成boss飞机
    else if(m_level>=6){

    }
} */

//槽函数
/****************************************************************************************************************************************/
void GameBackground::slt_newGame()
{
    m_scene->clear();
    init();
    //m_timer->start(UPDATETIME);
    gameStarted = true;
}

void GameBackground::slt_playerDead()
{
    //m_timer->stop();
    gameStarted = false;
}

void GameBackground::slt_startGame()
{
    if (gameStarted)
        //m_timer->start(UPDATETIME);
        emit sig_start();
}

void GameBackground::slt_pauseGame()
{
    if (gameStarted)
        //m_timer->stop();
        emit sig_pause();
}

// void GameBackground::slt_updata()
// {
//     //实现功能：
//     //    更新场景，和场景中所有的item对象
//     //    生成敌机
//     //    生成子弹包、炸药包、血包
//     //调用场景的advance()函数就会自动调用场景中所有图形项的advance()函数
//     //而且图形项的advance()函数会被分为两个阶段调用两次
//     //第一次void advance(int phase)中phase为0，告之所有的图形项场景将要改变
//     //第二次phase为1，在这时才进行具体的操作
//     m_scene->advance();
//     m_step++;
//     //更新普通NPC敌机和BOSS NPC敌机
//     if (m_step % 50 == 0 && !boss) {
//         CreateNPC();
//     }
// }

void GameBackground::slt_menu()
{
    if (gameStarted) {
        slt_pauseGame();
        //在munuwidget.h中声明了相关操作
        QScopedPointer<Menu> w(new Menu(true, this));
        //w.data()获取MenuWidget对象
        connect(w.data(), SIGNAL(sig_newGame()), this, SLOT(slt_newGame()));
        connect(w.data(), SIGNAL(sig_quit()), this, SLOT(close()));
        connect(w.data(), SIGNAL(sig_back()), this, SLOT(slt_startGame()));
        w->setModal(true);
        w->show();
        w->exec();
    }
    else {
        QScopedPointer<Menu> w(new Menu(false, this));
        connect(w.data(), SIGNAL(sig_newGame()), this, SLOT(slt_newGame()));
        connect(w.data(), SIGNAL(sig_quit()), this, SLOT(close()));
        w->setModal(true);
        w->show();
        w->exec();
    }
}

// void GameBackground::slt_addscore(int score)
// {
//     m_scores += score;
//     if (m_scores != 0 && m_scores % 50 == 0) {
//         m_level++;
//         if (m_level == 7)
//             m_level = 1;
//     }
// }

//事件处理函数
/****************************************************************************************************************************************/
void GameBackground::mouseDoubleClickEvent(QMouseEvent *event) {
    //设置event的accepted参数为true
    //accepted参数为true表示当前部件的事件接收器希望处理这个事件
    //accepted参数为false表示当前部件的事件接收器将这个事件的处理交给父部件进行
    event->accept();
    emit sig_menu();
}

void GameBackground::keyPressEvent(QKeyEvent *event) {
    switch (event->key()) {
    case Qt::Key_W:
        event->accept();
        emit sig_keyinput(0, 1);
        break;
    case Qt::Key_S:
        event->accept();
        emit sig_keyinput(1, 1);
        break;
    case Qt::Key_A:
        event->accept();
        emit sig_keyinput(2, 1);
        break;
    case Qt::Key_D:
        event->accept();
        emit sig_keyinput(3, 1);
        break;
    case Qt::Key_Space:
        event->accept();
        emit sig_keyinput(4, 1);
        break;
    case Qt::Key_J:
        event->accept();
        emit sig_keyinput(5, 1);
        break;
    default:
        event->ignore();
        break;
    }
}

void GameBackground::keyReleaseEvent(QKeyEvent *event) {
    switch (event->key()) {
    case Qt::Key_W:
        event->accept();
        emit sig_keyinput(0, 0);
        break;
    case Qt::Key_S:
        event->accept();
        emit sig_keyinput(1, 0);
        break;
    case Qt::Key_A:
        event->accept();
        emit sig_keyinput(2, 0);
        break;
    case Qt::Key_D:
        event->accept();
        emit sig_keyinput(3, 0);
        break;
    case Qt::Key_Space:
        event->accept();
        emit sig_keyinput(4, 0);
        break;
    case Qt::Key_J:
        event->accept();
        emit sig_keyinput(5, 0);
        break;
    default:
        event->ignore();
        break;
    }
}


// void GameBackground::createNPC()
// {
//     GenerateNpc::NormalNpcs fishplanes = GenerateNpc::ncreator(m_level, scene());
    
// //生成普通NPC飞机
// //     if (m_level < 6)
// //     {
// //         GenerateNpc::NormalNpcs fishplanes = GenerateNpc::ncreator(m_level, scene());
// //         foreach (NormalNPC *f, fishplanes) {
// //             int z =  RandAlg::creat(6);
// //             if (z == 1) {
// //                 int y = RandAlg::creat(SCENEHEIGHT / 2 - FISHSIZE);
// //                 f->setPos(0, y);
// //             }
// //             else if (z == 2) {
// //                 int y = RandAlg::creat(SCENEHEIGHT / 2 - FISHSIZE);
// //                 f->setPos(SCENEWIDTH - FISHSIZE, y);
// //             }
// //             else {
// //                 int x = RandAlg::creat(SCENEWIDTH - FISHSIZE);
// //                 f->setPos(x, 0);
// //             }
// //             connect(f, SIGNAL(sig_score(int)), this, SLOT(slt_addscore(int)));
// //         }
// //     }
// //     //生成boss飞机
// //     else if(m_level>=6){

// //     }
// }

void GameBackground::slt_upScore(int){
    m_scores += score;
}