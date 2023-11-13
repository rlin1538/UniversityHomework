/*
 Navicat Premium Data Transfer

 Source Server         : WJ
 Source Server Type    : MySQL
 Source Server Version : 50736
 Source Host           : localhost:3306
 Source Schema         : game_circle

 Target Server Type    : MySQL
 Target Server Version : 50736
 File Encoding         : 65001

 Date: 04/12/2021 19:07:05
*/

SET NAMES utf8mb4;
SET FOREIGN_KEY_CHECKS = 0;

-- ----------------------------
-- Table structure for collection
-- ----------------------------
DROP TABLE IF EXISTS `collection`;
CREATE TABLE `collection`  (
  `collectionID` int(11) UNSIGNED NOT NULL AUTO_INCREMENT,
  `userID` int(11) NULL DEFAULT NULL,
  `gameCircleID` int(11) UNSIGNED NOT NULL,
  PRIMARY KEY (`collectionID`) USING BTREE,
  INDEX `gameCircleID`(`gameCircleID`) USING BTREE,
  CONSTRAINT `gameCircleID` FOREIGN KEY (`gameCircleID`) REFERENCES `gamecircle` (`gameCircleID`) ON DELETE RESTRICT ON UPDATE CASCADE
) ENGINE = InnoDB AUTO_INCREMENT = 28 CHARACTER SET = utf8 COLLATE = utf8_general_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Records of collection
-- ----------------------------
INSERT INTO `collection` VALUES (1, 1, 1);
INSERT INTO `collection` VALUES (2, 1, 2);
INSERT INTO `collection` VALUES (15, 1, 5);
INSERT INTO `collection` VALUES (20, 2, 1);
INSERT INTO `collection` VALUES (21, 2, 2);
INSERT INTO `collection` VALUES (22, 1, 10);
INSERT INTO `collection` VALUES (24, 2, 10);
INSERT INTO `collection` VALUES (25, 1, 4);
INSERT INTO `collection` VALUES (26, 1, 6);
INSERT INTO `collection` VALUES (27, 1, 9);

-- ----------------------------
-- Table structure for comment
-- ----------------------------
DROP TABLE IF EXISTS `comment`;
CREATE TABLE `comment`  (
  `commentID` int(11) UNSIGNED NOT NULL AUTO_INCREMENT,
  `userName` varchar(255) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
  `postID` int(11) NOT NULL,
  `publishTime` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP,
  `commentContent` varchar(255) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL,
  PRIMARY KEY (`commentID`) USING BTREE
) ENGINE = InnoDB AUTO_INCREMENT = 16 CHARACTER SET = utf8 COLLATE = utf8_general_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Records of comment
-- ----------------------------
INSERT INTO `comment` VALUES (1, 'zwl', 1, '2021-11-30 10:35:50', '小伙伴们快来分享吧！');
INSERT INTO `comment` VALUES (2, '123', 1, '2021-11-30 10:36:27', '萌新求带！');
INSERT INTO `comment` VALUES (3, 'zwl', 1, '2021-11-30 15:01:42', 'hello，大家好');
INSERT INTO `comment` VALUES (4, 'zwl', 1, '2021-11-30 15:06:36', '1');
INSERT INTO `comment` VALUES (5, 'zwl', 1, '2021-11-30 15:07:03', '2楼');
INSERT INTO `comment` VALUES (6, 'zwl', 1, '2021-11-30 15:07:22', '沙发');
INSERT INTO `comment` VALUES (7, 'zwl', 4, '2021-11-30 15:16:16', '已经绝版了，拿不到了');
INSERT INTO `comment` VALUES (8, 'zwl', 3, '2021-11-30 19:27:58', '本周更新冬季');
INSERT INTO `comment` VALUES (9, '123', 15, '2021-11-30 22:17:22', '沙发');
INSERT INTO `comment` VALUES (10, '123', 23, '2021-12-04 17:20:16', 'hello');
INSERT INTO `comment` VALUES (11, '123', 1, '2021-12-04 17:28:17', '六楼');
INSERT INTO `comment` VALUES (14, '123', 1, '2021-12-04 17:33:15', '666');
INSERT INTO `comment` VALUES (15, '123', 1, '2021-12-04 17:42:26', '111');

-- ----------------------------
-- Table structure for gamecircle
-- ----------------------------
DROP TABLE IF EXISTS `gamecircle`;
CREATE TABLE `gamecircle`  (
  `gameCircleID` int(11) UNSIGNED NOT NULL,
  `gameCircleTitle` varchar(255) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL,
  `gameCircleContent` varchar(255) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL,
  `gameCirclePicture` varchar(255) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL,
  PRIMARY KEY (`gameCircleID`) USING BTREE
) ENGINE = InnoDB CHARACTER SET = utf8 COLLATE = utf8_general_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Records of gamecircle
-- ----------------------------
INSERT INTO `gamecircle` VALUES (1, '极限竞速：地平线4', '极限竞速：地平线4是一款Xbox开发的游戏', 'https://www.3dmgame.com/uploads/allimg/180613/276_180613213443_2.JPG');
INSERT INTO `gamecircle` VALUES (2, '穿越火线', '穿越火线是Smilegae开发的一款FPS游戏', 'http://p.ssl.qhimg.com/t018b1ff49405945651.jpg');
INSERT INTO `gamecircle` VALUES (3, 'CS:GO', '《反恐精英：全球攻势》（CS: GO）延续了 1999 年原作在团队竞技类游戏上取得的成就。 CS: GO 的特色包含全新的地图、人物、武器、全新的游戏模式，并提供翻新后的 CS 经典内容', 'https://www.csgo.com.cn/jpg/170414/10691492161133211.jpg');
INSERT INTO `gamecircle` VALUES (4, '人类一败涂地', '《人类一败涂地》是一款轻松搞笑的沙雕游戏，游戏的场景发生在飘渺的梦境之中。玩家既可以单机自闭，也可以最多八人联机一起欢畅。', 'https://nexusgames.to/wp-content/uploads/2020/08/Human-Fall-Flat-Free-Download-By-Nexusgames.to-p.jpg');
INSERT INTO `gamecircle` VALUES (5, '泰拉瑞亚', '挖掘，战斗，探索，建造！在这个动感十足的冒险游戏里没有什么是不可能的。世界是你的画布，地面是你的油漆。', 'https://image.9game.cn/2017/11/20/18624955.jpg');
INSERT INTO `gamecircle` VALUES (6, '古墓丽影', '《古墓丽影》探索了劳拉·克劳馥紧张又勇敢的起源故事，以及她从年轻女人变为坚强生存者的成长过程。 单凭原始本能以及超越极限的人类耐力，劳拉必须奋力揭开被遗忘的岛屿的黑暗历史，以逃离小岛无情的控制。', 'http://img1.gtimg.com/xian/pics/hv1/45/93/802/52173810.jpg');
INSERT INTO `gamecircle` VALUES (7, '古墓丽影:崛起', '劳拉解开的古老谜题使他陷入了与邪恶组织“圣三一”的恶战。她要赶在“圣三一”之前找到秘密。线索指向了“失落之城基特”的传说。劳拉明白她必须在“圣三一”赶', 'http://pic.3h3.com/up/2017-5/201752795239320420.jpg');
INSERT INTO `gamecircle` VALUES (8, '精灵与萤火意志', '在充满异域风情的广大世界中开启全新旅程，征服强大的敌人，解开极具挑战性的难题，在一次次任务中，揭开奥里的命运。', 'http://store-images.s-microsoft.com/image/apps.18799.14047496556148589.9fda5cef-7995-4dbb-a626-66d2ab3feb4f.1e167626-8b7d-47b4-9fe5-d06a43ac6677');
INSERT INTO `gamecircle` VALUES (9, '生化危机2', '一切都凌驾于玩家的想像之上。 一场生化灾难於1998年9月袭击了浣熊市，从残害幸存者的丧尸地狱中生还吧。 无尽的刺激、引人入胜的故事和无法想像的恐怖正在等候你。 见证系列首屈一指的杰作──《Resident Evil 2》的重生吧。', 'https://www.ign.com.cn/sm/ign_cn/screenshot/default/feng-mian_5d7z.jpg');
INSERT INTO `gamecircle` VALUES (10, '英雄联盟', '《英雄联盟》简称LOL）是由美国拳头游戏开发、中国内地由腾讯游戏代理运营的英雄对战MOBA竞技网游。游戏里拥有数百个个性英雄，并拥有排位系统、符文系统等特色养成系统。', 'https://uploadfile.bizhizu.cn/2016/1202/20161202093020401.jpg');

-- ----------------------------
-- Table structure for post
-- ----------------------------
DROP TABLE IF EXISTS `post`;
CREATE TABLE `post`  (
  `postID` int(11) UNSIGNED NOT NULL AUTO_INCREMENT,
  `postTitle` varchar(255) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL,
  `poster` varchar(255) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL,
  `postContent` varchar(255) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL,
  `postTime` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP,
  `postCircle` int(11) NULL DEFAULT NULL,
  PRIMARY KEY (`postID`) USING BTREE
) ENGINE = InnoDB AUTO_INCREMENT = 25 CHARACTER SET = utf8 COLLATE = utf8_general_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Records of post
-- ----------------------------
INSERT INTO `post` VALUES (1, '欢迎来到地平线4', 'zwl', '这里是地平线4游戏圈', '2021-11-24 11:14:55', 1);
INSERT INTO `post` VALUES (2, '欢迎来到穿越火线游戏圈', 'zwl', '大家快加入吧，九亿鼠标的枪战梦', '2021-11-28 20:58:20', 2);
INSERT INTO `post` VALUES (3, '地平线4新赛季来啦', 'zwl', '本周四即将更新本月的春季嘉年华，快来游玩吧', '2021-11-29 20:11:25', 1);
INSERT INTO `post` VALUES (4, '求助：如何获取AE86车辆', '123', '有大佬知道怎么得到AE86车辆吗？十分想要', '2021-11-29 20:12:54', 1);
INSERT INTO `post` VALUES (5, '请问这个赛季任务如何完成', 'zwl', '求求大佬解惑', '2021-11-29 22:05:58', 1);
INSERT INTO `post` VALUES (8, '123', 'zwl', '测试', '2021-11-29 22:19:55', 1);
INSERT INTO `post` VALUES (9, '测试', 'zwl', '123456', '2021-11-29 22:20:52', 1);
INSERT INTO `post` VALUES (10, '有人吗', 'zwl', 'hello', '2021-11-29 22:22:33', 1);
INSERT INTO `post` VALUES (11, '测试', 'zwl', '测试', '2021-11-29 22:23:54', 1);
INSERT INTO `post` VALUES (13, '欢迎来到古墓丽影游戏圈', 'zwl', '这里是古墓丽影游戏圈，欢迎大家来发帖，一起和劳拉去冒险吧', '2021-11-29 22:27:12', 6);
INSERT INTO `post` VALUES (14, '劳拉好帅', 'zwl', '劳拉好帅', '2021-11-29 22:35:14', 6);
INSERT INTO `post` VALUES (15, '穿越火线', 'zwl', '穿越火线。', '2021-11-29 22:39:44', 2);
INSERT INTO `post` VALUES (16, '欢迎来到泰拉瑞亚的游戏圈', 'zwl', '喜欢冒险的朋友们快玩泰拉瑞亚吧', '2021-11-30 15:21:49', 5);
INSERT INTO `post` VALUES (17, '好久没玩了', '123', '好久没玩穿越火线了，上一次玩还是上一次', '2021-11-30 22:18:21', 2);
INSERT INTO `post` VALUES (22, '。。。', '123', '。', '2021-12-04 17:15:46', 2);
INSERT INTO `post` VALUES (23, '欢迎来到生化危机2游戏圈', '123', '欢迎大家', '2021-12-04 17:18:55', 9);

-- ----------------------------
-- Table structure for user
-- ----------------------------
DROP TABLE IF EXISTS `user`;
CREATE TABLE `user`  (
  `userID` int(11) UNSIGNED NOT NULL AUTO_INCREMENT,
  `userName` varchar(255) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
  `userPassword` varchar(255) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
  `userPhoneNumber` varchar(11) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
  `userState` tinyint(1) UNSIGNED ZEROFILL NOT NULL COMMENT '管理员为1，普通用户为0',
  PRIMARY KEY (`userID`) USING BTREE
) ENGINE = InnoDB AUTO_INCREMENT = 6 CHARACTER SET = utf8 COLLATE = utf8_general_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Records of user
-- ----------------------------
INSERT INTO `user` VALUES (1, 'zwl', 'zwl', '13799482633', 1);
INSERT INTO `user` VALUES (2, '123', '123', '12345', 0);
INSERT INTO `user` VALUES (3, 'aaa', 'aaa', '1111', 0);

SET FOREIGN_KEY_CHECKS = 1;
