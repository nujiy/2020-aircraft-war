# 三轮实现在总体功能实现占比
1. 显示游戏界面
- 游戏开始界面（二轮实现）
- 游戏进行界面（一轮实现）
- 游戏结束界面（一轮实现）
- 其他界面，包括游戏操作说明、游戏配置界面（二轮实现）
2. 游戏运行功能
- 玩家基本操作功能：移动飞机（一轮实现）、发射子弹（一轮实现）、发动大招（二轮实现）
- 玩家高级操作功能（选做）：拾取弹药包（√）、发射炮弹（√）、其他额外功能（√）
- 基本NPC：移动（一轮实现）、攻击（一轮实现）
- Boss NPC：移动（二轮实现）、攻击（二轮实现）、大招（二轮实现）
3. 游戏配置（选做）
- 进度保存（ ×）
- 难度分级设置（ ×）
- 多媒体：音乐（ ×），开场（ ×）、转场动画（ ×）等
- 其他配置设置（ ×）

# 第三轮迭代实现内容
1. 包操作
    1. 实现玩家飞机拾取技能包，释放技能。
        - 拾取弹药包，补充子弹。
        - 拾取炮弹包，发射有限枚炮弹。
    2. 实现不同属性子弹与NPC的交互。
        - 改变子弹的攻击范围。
        - 改变NPC受到不同属性子弹攻击，被消灭时的动画。
2. 代码优化
- 检查并完善MVVM设计模式的实现。
- 代码重构。改变涉及多态、虚函数等的代码实现；在接口不变的情况下提高函数性能。

# 其他内容实现
若在三轮实现之后仍有时间，或小学期结束后希望完善游戏项目，则实现游戏配置部分。
