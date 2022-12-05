# HW5-Bookstore-2022

## Information

Project name: Bookstore

Author: Conless Pan

## Classes

The main class Bookstore is 

```cpp
class Bookstore {
  public:
    Bookstore();
    ~Bookstore();

    void ReadData();
    void PrintData();
    void OperateMsg(InputMsg);

  private:
    UserSystem users;
    BookSystem books;
};
```

Class UserSystem is 

```cpp
class UserSystem {
  public:
    UserSystem();
    ~UserSystem();

    void UserRegister(const std::string &user_id, const std::string &user_password, const std::string &user_name);
    void UserLogin(const std::string &user_id, const std::string &user_password);
    void ModifyPassword(const std::string &current_password, const std::string &new_password);
    void UserLogout();

  private:
    std::unordered_map<std::string, BookstoreBaseUser *> user_table;
    BookstoreBaseUser *current_user;
};
```

Class BookSystem is

```cpp
class BookSystem {
  public:
    void SearchByISBN(const std::string &isbn);
    void SearchByName(const std::string &name);
    void SearchByAuthor(const std::string &author);
    void SearchByKeyword(const std::string &keyword);

    void BuyBook(const std::string &isbn, const int &quantity);
  private:
    std::string sel_isbn;
};
```

Besides, the log system and finance system are also need to be correctly stored, and that was done in Bookstore.cc.

## File structure

```
HW5-Bookstore-2022
├─ CMakeLists.txt
├─ docs
│  ├─ bonus.md
│  ├─ README.md
│  └─ requirements.md
├─ README.md
├─ scripts
│  └─ build.sh
└─ src
   ├─ Book
   │  └─ BookSystem.h
   ├─ Bookstore.cc
   ├─ Bookstore.h
   ├─ CMakeLists.txt
   ├─ Exception.cc
   ├─ Exception.h
   ├─ main.cc
   ├─ User
   │  ├─ BookstoreBaseUser.h
   │  ├─ BookstoreManager.h
   │  └─ UserSystem.h
   ├─ utils.cc
   └─ utils.h

```
```
HW5-Bookstore-2022
├─ .clang-format
├─ .git
│  ├─ COMMIT_EDITMSG
│  ├─ FETCH_HEAD
│  ├─ HEAD
│  ├─ ORIG_HEAD
│  ├─ branches
│  ├─ config
│  ├─ description
│  ├─ hooks
│  │  ├─ applypatch-msg.sample
│  │  ├─ commit-msg.sample
│  │  ├─ fsmonitor-watchman.sample
│  │  ├─ post-update.sample
│  │  ├─ pre-applypatch.sample
│  │  ├─ pre-commit.sample
│  │  ├─ pre-merge-commit.sample
│  │  ├─ pre-push.sample
│  │  ├─ pre-rebase.sample
│  │  ├─ pre-receive.sample
│  │  ├─ prepare-commit-msg.sample
│  │  ├─ push-to-checkout.sample
│  │  └─ update.sample
│  ├─ index
│  ├─ info
│  │  └─ exclude
│  ├─ logs
│  │  ├─ HEAD
│  │  └─ refs
│  │     ├─ heads
│  │     │  └─ main
│  │     └─ remotes
│  │        └─ origin
│  │           ├─ HEAD
│  │           └─ main
│  ├─ objects
│  │  ├─ 00
│  │  │  └─ 5e7f4de6f32c2fc9f5f6820867943598442ba2
│  │  ├─ 01
│  │  │  ├─ 7970d0f0543e3068c541c9048e539cb3201a18
│  │  │  └─ ad4773121b0f271a1fd29e3f607ca48770e8f9
│  │  ├─ 02
│  │  │  ├─ 9d7f7a3c9fdd8fdede5993f14dde69a4c2b1c1
│  │  │  └─ b035f84ef9993b674a4a310eed6b874b82e063
│  │  ├─ 03
│  │  │  ├─ 44dd7fb8fd9bb6dc66a1b99d4e4ae4ece53977
│  │  │  └─ d87bdcd1f86a0b2b1e150862acb59e1562fb67
│  │  ├─ 04
│  │  │  ├─ 6c663e21a73e706cd2c589a42c78a0141c0229
│  │  │  ├─ 9d3dbba5be46ad652fc9566bc7fc8a677f53f4
│  │  │  └─ a2ec539cc4589204eccffb37768b85f319bb82
│  │  ├─ 05
│  │  │  └─ 527fd2615712408a0a17deb9a662b9785dbe6a
│  │  ├─ 06
│  │  │  ├─ 01e7c9ce2d23501a44bba1150020d2793da7d9
│  │  │  └─ feb68318d7cbb72de79bd29aeddd224489e384
│  │  ├─ 08
│  │  │  ├─ 0cf1b16f9f678f7de43f981eeaac9c76b5601c
│  │  │  ├─ 6830f2d7797faa108bc92f5ee5fa2931a7f846
│  │  │  └─ dfd72e6619d93271a31704be90f9fc73c6bc92
│  │  ├─ 09
│  │  │  ├─ 29e1a7b52588219b23257ee7a500e7037d101f
│  │  │  └─ 31a4c0b4db1d5065439cefaf1da85790028af6
│  │  ├─ 0a
│  │  │  └─ b9cf51c01c222e794f969352df1c36fb400ade
│  │  ├─ 0b
│  │  │  └─ 7bb401b4dddec9a4b53fecfe33d542f964f094
│  │  ├─ 0c
│  │  │  ├─ 68aae9e125e3126aa6b2fe6a9873de05eaa893
│  │  │  └─ 7e5b104ec5eb71c5e3982060479e0010564944
│  │  ├─ 0d
│  │  │  ├─ 891ea243d4a8c9c8c66dca530d1817706829ad
│  │  │  └─ a7ebc1e08c047bfef49d445eddc0e64affc443
│  │  ├─ 0e
│  │  │  ├─ 474e5886b433953294ee7a0de1a44adc450f1a
│  │  │  └─ 7f3e9f568e9e1af54e87bdcbe3d0ba3b49d4e6
│  │  ├─ 0f
│  │  │  └─ 956ac7d4b99ecf54edc710da8092e60fc8d99c
│  │  ├─ 11
│  │  │  ├─ 1b86a78144774dbbdba5d88d238efa555d8feb
│  │  │  ├─ 490320077eec07ff176e8aa6c9e0942fb9474b
│  │  │  ├─ 4d1c70a8c5721d2fa90cfba160355b141d4c94
│  │  │  ├─ dac2476081ac33f08037dece1b6feee5a280dc
│  │  │  └─ ea9ca61ad4b74863238f446714f9dfecb72c89
│  │  ├─ 12
│  │  │  ├─ 539dd48f3a4c285b117a2212fa80ff80fbacaf
│  │  │  ├─ 576dbbcb14ac64f70cc4144c45518ff9caf837
│  │  │  └─ 5f0c09e035a0f775d7b8258292524d98be4a1e
│  │  ├─ 13
│  │  │  └─ 9f9243035bb3615edeaadf3121a31bb5dde838
│  │  ├─ 15
│  │  │  ├─ 9d5f4255c8b8fca67944636a627a5c211e14e9
│  │  │  └─ f32b3a67ff865ff796f59f10b3de04887ef168
│  │  ├─ 16
│  │  │  ├─ 200377f117b877cf78e393fd13d4b52c022d31
│  │  │  └─ f20e02f286a133293aa2d8737082bf7eff19f4
│  │  ├─ 18
│  │  │  └─ c58de229993071988959d6f235664e08b37f54
│  │  ├─ 19
│  │  │  └─ 83d631a67a4be165b7d35ba7fbef7dd8db05d5
│  │  ├─ 1a
│  │  │  └─ 1702ffcecd80b34f8f37e3f890616990f22f89
│  │  ├─ 1b
│  │  │  └─ 6c15f225865c3b9b7b6e593c8ee86a54bb85a5
│  │  ├─ 1c
│  │  │  ├─ 432255a343a57555c5594037dd13a4e080904e
│  │  │  └─ 4a171a6bca720df93d76f8331a21860b72758f
│  │  ├─ 1d
│  │  │  ├─ 2bf3c2b0487e6923efc7c678ce971dc0b3c2fd
│  │  │  └─ 33ff1857cd1af7f82d9cb6764efe689e5a0fad
│  │  ├─ 1e
│  │  │  ├─ 5e37f1471ee3efc582a8b888dbdab02a3fa791
│  │  │  └─ 99b80522c70cce369f726886b5182554be9dbd
│  │  ├─ 1f
│  │  │  ├─ 9d06a7cff856592725be20a9a49cf5c9d65530
│  │  │  ├─ b87f90c1e8a8d9240fa284e10aa603b8b3c566
│  │  │  └─ e3689aa78ccaee9e3aa0b9cfd3081d131b05ad
│  │  ├─ 21
│  │  │  ├─ 0cba13597c0a500928161447d14513c570ecc4
│  │  │  ├─ 64417c3872504ff46e340e58833632a8b03ea9
│  │  │  └─ d26c6a2bd40f0de741b6042433ef843c16372c
│  │  ├─ 23
│  │  │  ├─ 3e0f91236974e43271ed562f6a951b6ad4c24e
│  │  │  ├─ 46a701d11728b34889db8af0acce08c53fcc9d
│  │  │  └─ 83fa8b4f3eb128d3fdb199c3eca9739fc74984
│  │  ├─ 24
│  │  │  ├─ 34b39e29897bd1a8d59af72ecccfe32cb1eecd
│  │  │  └─ 721c487812052cd2c8bdd5e863e77616e3264a
│  │  ├─ 25
│  │  │  └─ a459350a44b65b4cb92fad56c4678e46186867
│  │  ├─ 26
│  │  │  └─ 9d822e521ba872a2b92f21eb40c3d41f3d606c
│  │  ├─ 28
│  │  │  └─ aa5f028562029b449567e1a35750ff4a7c9e59
│  │  ├─ 29
│  │  │  └─ 68ff5bda3097e7826e82a7708dbdb41b84b88a
│  │  ├─ 2a
│  │  │  ├─ 49f8e7a454968e7e5f002e7d6181f511b600ec
│  │  │  ├─ 5e7eadcf45e01623925a70383ef2ef8059cdc8
│  │  │  ├─ 6f44171c5f24b59e764eddbbc98f0f45c980ed
│  │  │  └─ d6850e5d175be9b28696aaad0595ba8b2255a1
│  │  ├─ 2b
│  │  │  ├─ 236b3f6a3e9cacd1c7dec7b7e3db5954624367
│  │  │  ├─ 37c16a47b6bec6d648c7340ffc586b3e6c9cfc
│  │  │  └─ 4654ecc04ece4c57ee4cef23a5e2361deab5aa
│  │  ├─ 2d
│  │  │  └─ 709ff7cb9b7bdb119ffbe732c71fa15fbe4290
│  │  ├─ 2e
│  │  │  ├─ 9aca7e924c286283a8e4381e7249a4d8d82ec3
│  │  │  └─ a9b1b78b287cb148d0dfe9703346ac9e2e7ca7
│  │  ├─ 2f
│  │  │  ├─ 0f2213bc923ededc2ed1048a085560c50eb013
│  │  │  └─ 9c16191f2d71a10f9e5fa222cf279420978921
│  │  ├─ 30
│  │  │  ├─ 4c57c0ba79f3327921163cbd02cdd3c0faffa4
│  │  │  ├─ 615e36cf4ae2670a80dc792818c0ff619701db
│  │  │  └─ b53395b6ad3a03c7f3168cab48578a04be8f5a
│  │  ├─ 31
│  │  │  ├─ 47747b01dd9d2d99225d615a75bd7895ba7e22
│  │  │  ├─ 4c40e3afa7dda83e4d0364e990c332b341915e
│  │  │  └─ d8f41877ffaf8022220b3eedaa464f3aa45b84
│  │  ├─ 33
│  │  │  ├─ 11550aed77bf950735ac79a315a0beabf8d047
│  │  │  └─ faa31d45f6f14e51a27349b05a616b929fa33b
│  │  ├─ 34
│  │  │  └─ a3d571f19ce56d4045721736fb28b7440718a2
│  │  ├─ 35
│  │  │  ├─ 0b69af37325a5c1060b78b110bf10d5a0cceec
│  │  │  ├─ 1489666c8e3526046897ab783512cb34492e9a
│  │  │  ├─ 3716365fe04734af88dce5217f177e28062ed6
│  │  │  ├─ a3303fe4f19da13ea6ae2e99f7ea517af44274
│  │  │  └─ e03557bdc20930c86701bee32458252d1e2600
│  │  ├─ 37
│  │  │  ├─ 1c820fbf2043f9670c366549b88b0552f0704a
│  │  │  └─ 7937462ce42db7cef8177abc3f78d282c6243f
│  │  ├─ 38
│  │  │  ├─ 3a738efe3a28a104b3d7faad08b90d6e305dae
│  │  │  └─ 6d4f99bd212a5a4879733f5e535c3e4756ebdd
│  │  ├─ 39
│  │  │  └─ cbd62f86a3131ab6b37743add6f4b44ed34d64
│  │  ├─ 3a
│  │  │  ├─ 25f9450212bcd4a8c059d362e0ae9843130806
│  │  │  ├─ 2cd05bda83ea97aaec9fe840bf821c61c72e7b
│  │  │  ├─ bb58d8bc1d1daf35e018eaa552a0cb1ec03bac
│  │  │  └─ ee41ffe2804c19668130dda8be9ad6d244326c
│  │  ├─ 3b
│  │  │  ├─ 27eec42dea50887c63abe5a0fade7c21f27eb8
│  │  │  ├─ 3ba4bdbcfb8987f53d3441097014a97173bea0
│  │  │  ├─ 6d109214f17e00ee616c9b305740cf38706fe2
│  │  │  ├─ 9c3cb3fba92a3091815303fc5badd73c6d2235
│  │  │  └─ fc3cc2fe95930e40026c9a4d9a7c6e678fac56
│  │  ├─ 3c
│  │  │  ├─ 5fb8e31d44bbfd81e4257d50a6e96a26f66cb7
│  │  │  └─ b51f29c6fc26ff2c2cc60a25a47203d8c69c98
│  │  ├─ 3d
│  │  │  ├─ 141c74bd7b19451f6771579dc9b1bf3df232c3
│  │  │  ├─ 46c83cab716a7b18a259a75b0224bf7922b0c6
│  │  │  ├─ 52fd33e251af76089b91b0545da198a1fd4055
│  │  │  ├─ 60c4f195f6c26abd38582f0f5d7037cd7102cd
│  │  │  ├─ a5a3e70e24cb9d15f7cf1f80d2959dd7d2c911
│  │  │  └─ b48cfd4568fc575df2924afd1af042d46a0685
│  │  ├─ 3e
│  │  │  ├─ 12071f908a484fbad61cbcda0a02a89da3d1ef
│  │  │  ├─ 1edfa8f7eb9bdffabbf374f79ec75e65da6784
│  │  │  ├─ 7135699d6a0f364a11a6bf35e3d01968d6272b
│  │  │  ├─ ac87ef639c2ee5d7e52e0044029807b72243a5
│  │  │  └─ f763411304c0cd0a9bf3b563d0a40b1c6bb73e
│  │  ├─ 3f
│  │  │  ├─ 079d68c5df5ddd20d164a6011419593fda9c6f
│  │  │  ├─ 6ee100907f0eab3452660fee67680c2e71a82a
│  │  │  ├─ 7768ba8058d37bbfd44f13555cb040a80044ce
│  │  │  └─ 92e5c02c4969b03959f9efa7f197338e0420c5
│  │  ├─ 40
│  │  │  └─ 815d4566f9768929948387b2cd9e9f992fc729
│  │  ├─ 41
│  │  │  └─ 91153711c6495a96d286268384f1182b2c78dc
│  │  ├─ 42
│  │  │  └─ a883982a0fc14acc1bca778ef6f944473d4626
│  │  ├─ 43
│  │  │  ├─ 497956f63d6ebe6c31aabcbe95f2ff0cf505a4
│  │  │  ├─ 4cb3d1837ee6d88e5d4e7e8844629726990db7
│  │  │  └─ ab3d37a585cae0566e76aceebe0a694015116f
│  │  ├─ 45
│  │  │  ├─ 460830857bad8dcfdb655d517a20b4768ab4ea
│  │  │  └─ 8e58de25b597e262991cee5a47105cd540388e
│  │  ├─ 46
│  │  │  └─ 4aca5bd3e3a4ffab997094c6e22e7670e4e7c0
│  │  ├─ 47
│  │  │  └─ 243cc7543507eead7a86d8a9d87044ff50601d
│  │  ├─ 48
│  │  │  └─ e298f6d879a34779a27a8573a81a9ea9e1b6d6
│  │  ├─ 49
│  │  │  └─ 7d86a2d146c003e7b09f1f373ed87937aa2609
│  │  ├─ 4b
│  │  │  ├─ 3766b57d4e3ed9f2a5c44aca0af177951a584a
│  │  │  ├─ 557ec8c64ac15571c962f0b7ef0caf0935d13d
│  │  │  └─ fd4e3a916934f990aa83bb7a428c98f258d78e
│  │  ├─ 4c
│  │  │  ├─ 571a43ab5f43d2f7398d5337d80cf7e1162047
│  │  │  └─ 5e575f58515baad3fb4a1fd72ee02fa560bf10
│  │  ├─ 4d
│  │  │  └─ e0c20f59c0bbab044ca591b796b979f3fbce04
│  │  ├─ 4e
│  │  │  └─ 3e75403507c4d28e89af1e811f72c9a8291f3d
│  │  ├─ 4f
│  │  │  ├─ 5f9466ed3111fb138abe0a952786fcec426881
│  │  │  ├─ a9df1cabbd15bbaaf670a3f7162c2d5c6ba064
│  │  │  ├─ ac74a57a23dee043d209b9e3ceb7eab4f47895
│  │  │  ├─ b0ad086ac6d13a844614c839a621eb6f46507a
│  │  │  └─ cc20270c1c5fb368819989f4a2977c4a766d93
│  │  ├─ 50
│  │  │  ├─ 3fb9284dcf0da558e45b72d2ab0478a15da050
│  │  │  └─ 6b10690c9deb349bcfaa9aff1b79783368b165
│  │  ├─ 51
│  │  │  ├─ 0e52b8ccda8510a1e1aa1e13b151891b8f68d0
│  │  │  ├─ 4261e31dc9e1b627096c713011045eaba69822
│  │  │  └─ ac5f03a41592ceb29b552ff7dcc991702ec087
│  │  ├─ 52
│  │  │  └─ 7f7b18d28f838d3e92bfe9aa66dca452ca48b4
│  │  ├─ 53
│  │  │  ├─ 13dbb6d1cfea914d53931907ece0b86eb7a748
│  │  │  ├─ 49a489c226d4ec2bf60a84157f648d2a302029
│  │  │  └─ 516aa346788bd5b1471d2c37d08447d62033da
│  │  ├─ 54
│  │  │  ├─ 6c6a0b8f17a60a06cbfd2376930ed705396126
│  │  │  ├─ 924ca20bd19173a6d3f90104021a3181fdb9b8
│  │  │  └─ cc2fa1be1d976a4cd8839bd7d1e202a9fed9fb
│  │  ├─ 56
│  │  │  ├─ 90c59d873fa83fd08d800c45d4410cdcb72520
│  │  │  └─ af7b2957ad10b700bdbeccd9b85a1fc213e35c
│  │  ├─ 57
│  │  │  └─ 5212e2530b2a97d1322aefa179ed1c6ec706dc
│  │  ├─ 58
│  │  │  ├─ 50e94ea576e22879542562890226ef5e1c9479
│  │  │  ├─ 805509ca2aacc6994ea794fef0105d7cf924b7
│  │  │  └─ fcb6baeffdc61e70da2c03f6bc2a50fdc22592
│  │  ├─ 59
│  │  │  ├─ 2218795023334ec3a33e439b2e60400a904c4d
│  │  │  ├─ 39e3f06934a45253495ca11fe2b3ffb16cea0e
│  │  │  ├─ af7ed638557686652ea23b50a96e91ddc56730
│  │  │  ├─ cb18576d2386de73e577685d08024d1c9c69f2
│  │  │  ├─ f3dde3905eb86c8abdd4c647396231f74127ce
│  │  │  └─ fee91a1f14ec926440ab0d3717f6a9bf69ab1a
│  │  ├─ 5a
│  │  │  └─ 4a1597bfbbc81159bea37d5382507bf3a35443
│  │  ├─ 5b
│  │  │  └─ cc8ce79e3285c2e6d4ad24527bbec4282a69ea
│  │  ├─ 5c
│  │  │  └─ d50cf00cef872a946487fc5cd6c0c1fe0524f1
│  │  ├─ 5e
│  │  │  ├─ 54f903a3959f46fe7136169ffb6dd8737619d7
│  │  │  └─ e27bfa5581ee4afab86f3d018f7c8138f1aa28
│  │  ├─ 5f
│  │  │  ├─ 75c92b97b48b8f40212f6beb1caaccca9695d2
│  │  │  ├─ a8bb35a356da5ef5b6adcd5f6f8e58ed6a8277
│  │  │  └─ c75af6b63235580ebd347402b61a8273676c53
│  │  ├─ 60
│  │  │  ├─ 3c826032e4ff85a36b502a99d343f5922f79f4
│  │  │  ├─ 3d2eb455e2e723e28d823532c9abff244d6e3a
│  │  │  ├─ 631708aabcc5628ee6d42ce71ed1c644cd8738
│  │  │  ├─ 904fe6b52d9137dfe1eed17fa5095476cc8317
│  │  │  ├─ 9ec087c400c52772c5de7b759b0b695ea8a196
│  │  │  └─ dadcc861e246e57b90b38268647700888e939b
│  │  ├─ 61
│  │  │  └─ 1ac70d90dc71f6f09635f50e3fc17146b486fe
│  │  ├─ 62
│  │  │  ├─ 2d1f2f7087384508f2f2a3c83870607f67437b
│  │  │  ├─ 87e9e213f12b558ac405675f7143f0c8aba22a
│  │  │  └─ dd2c76fd2d134f08fcb4706c0deea895d8b2db
│  │  ├─ 63
│  │  │  ├─ 7c42a1278016cc0c3d63c95b9e7d70825a2e3d
│  │  │  ├─ 8626ed73dc78ffacf704bab7d4a9beafd233e8
│  │  │  └─ 92be8d9daa9c2fc6828c8b512ac30e4fc40f69
│  │  ├─ 65
│  │  │  ├─ 893224d5474eade036f158bea25161246927b4
│  │  │  └─ fdd62de1a9a0a89fa6ffdc932dee90645ead0c
│  │  ├─ 67
│  │  │  └─ 6a9beaa59dd5cf3cdca1f54d19a2eef88e68a6
│  │  ├─ 68
│  │  │  ├─ 54e1c022a48742ef3b4786b78910ac9e3faa54
│  │  │  └─ d286ed3e6e53d8e2643592977f2a7309d62338
│  │  ├─ 69
│  │  │  ├─ 2b9408f6699e1438aa4422ada601d92c15f4fb
│  │  │  └─ ce9568333c3cf51b344390531d104feb9db263
│  │  ├─ 6a
│  │  │  ├─ 51697df2e03f691e6a2e21b6639d6206710bbf
│  │  │  ├─ 7838212a2a6814007ca795e6e5cb7fe3ef4b3c
│  │  │  └─ fd2eb74c4441127a94357e3d9bf26874154d08
│  │  ├─ 6b
│  │  │  ├─ 80fbab0e4ced2c370fdcba785aa9c1852cb261
│  │  │  └─ f7c90835ee664e12323657d3d39f5ee7d31ccb
│  │  ├─ 6c
│  │  │  └─ 77efbe702fc01e2bdc811e4aac87f994343720
│  │  ├─ 6d
│  │  │  └─ f0e7cc6c8f5e6ffa4f167acbf6af4859be3d8a
│  │  ├─ 6e
│  │  │  ├─ 007db7edc6ce3f7226669901131e63065fb413
│  │  │  ├─ 031efaa09c5a2096e488f9115eb63563c09eff
│  │  │  ├─ 0350053e9ac5ed826f96a59c0aab9dffc14ead
│  │  │  └─ f40a6cb2a399ebd3ad57dffd4563e999076c93
│  │  ├─ 6f
│  │  │  ├─ 51a24d5feb33bcb6cc36acf9d019f452d8e72b
│  │  │  ├─ 947ff317a4aa253f9e7ec0bd49dbe6fb064753
│  │  │  └─ abf9ba5bf71884041cd26ba84aed4fd34a9a43
│  │  ├─ 70
│  │  │  ├─ 426be96e200b50207f87ee6f7315fbc9c5d511
│  │  │  └─ 4b9de7cdf6acb2454274aecb6d90c803c32567
│  │  ├─ 71
│  │  │  ├─ 7e6c682a967bf626cfe3e02f97b2acac926951
│  │  │  └─ f6d9501f628f782b500a2bf507f60f4b71049f
│  │  ├─ 72
│  │  │  ├─ 65b9188fc4165cba16262d99dc6508544f88cc
│  │  │  ├─ a4d223a8aad5e4e1ce05ecacf1aa307484a757
│  │  │  └─ c38d333b6af06f0ab9e572ce9c304b51f18b99
│  │  ├─ 73
│  │  │  ├─ 00714432d2916f6a5cecc61fc25e7612582039
│  │  │  ├─ 1ffe6ff1cecfacf13f3f09dde62726b1b48ec8
│  │  │  ├─ 31b35e37542cbc280a58897996ad4ca989bcdd
│  │  │  └─ 8b098935ff49d1c046826b7677cb8a6b500fa5
│  │  ├─ 74
│  │  │  ├─ e4d32330c953bc71b9700c313b7ef54d083117
│  │  │  └─ f96a6ab183fee383c77c7b935f2ff326b6c6f8
│  │  ├─ 75
│  │  │  ├─ 24cde237bda9923f9448c3e95f3f1b73fa2a9d
│  │  │  ├─ 6d9324d1f8d8a133dd63a2d2e4e3149aef19e6
│  │  │  ├─ c0c8068bc974cdfe7b1bb11a2123d7499e4326
│  │  │  └─ ebc2a9163c5eaeaaf13d57a281d79a34fb0344
│  │  ├─ 76
│  │  │  ├─ 6f63b7bb16e1f8f0eedc08a28e7c3a2ca84465
│  │  │  ├─ 93f37e98c4a6956f39b0a778c1f1d79bed5868
│  │  │  ├─ ab0861974f1bd4878d4000e7d1a50604797d55
│  │  │  └─ ccfd5cfda73f159923932ace0ec69d3ade1ea9
│  │  ├─ 77
│  │  │  └─ 418d7b6be47ce311cb272b3068466f86339f1e
│  │  ├─ 78
│  │  │  └─ ac16e05368a9e4731a4820626e13d94867079d
│  │  ├─ 7a
│  │  │  ├─ 3746195ea71c314c627ce1bb8046411bdd9bed
│  │  │  └─ 4edcc32a9ff3d2e813decfb7e7dac8c8680cf2
│  │  ├─ 7b
│  │  │  ├─ c03c76419fabe059bf17e2abe4351f67f0f867
│  │  │  └─ ffb0c193907e13ef9e9cb6e2c664d9a447c2c7
│  │  ├─ 7c
│  │  │  ├─ de6068e2d4d1068e72329a9d7cab235ace61c5
│  │  │  └─ ed9120fc029eeaaf1db0c54fe9ca48dd970828
│  │  ├─ 7d
│  │  │  └─ e1576b54e9c4d23da27424c4e90e0b7b50483d
│  │  ├─ 7e
│  │  │  └─ 6234e41e4e486c145b98f0fd9eb4c8225ade64
│  │  ├─ 7f
│  │  │  └─ b5467773c6b585e43e5f4d1b5d8f9b25688dd1
│  │  ├─ 80
│  │  │  ├─ 10c8d0de2cdcc18684b376f9616da7eb235e64
│  │  │  ├─ 3c1a72b4086cc0ee9fda2c4e059b99d1b2e727
│  │  │  ├─ 9d53d405496315a52b86afacdf4130eb9031c7
│  │  │  ├─ c9493edcacecdad139617170abc97bcd29eb73
│  │  │  └─ e1d7d16edf53e8eba388443e6833013f8600d5
│  │  ├─ 82
│  │  │  ├─ 04602301c6f1abd281a351a31383139b0a66f3
│  │  │  └─ 590fb60cb5d5ba2751250d278fafbd4e287e47
│  │  ├─ 83
│  │  │  ├─ 4ef343bca6b7c20a5b7c4e086f61b2c8485109
│  │  │  ├─ 611c846e34a8b7e086fb1fb03be910aeb8c762
│  │  │  └─ edebfd3efcc3b6776b1840d7a1fa36434e017e
│  │  ├─ 85
│  │  │  ├─ 5574a5091b3172b78a6d5edeb64f9d93e2dc48
│  │  │  ├─ 69d1c1aeef83a8491966c408fce2327db253e6
│  │  │  ├─ 9eb9c323df0f32a18e5a8ee2da763d2670d868
│  │  │  └─ a1b732b49069119363f6699d277b5bb379af50
│  │  ├─ 86
│  │  │  └─ 46a93803c9eb681cda22ff97e182e512f94e3e
│  │  ├─ 88
│  │  │  └─ 87a976fefa2eee970272c7b7087580808b3e4e
│  │  ├─ 89
│  │  │  ├─ 503ade3f3728d1ab457077d0bf0d5649cc660c
│  │  │  └─ 6777fd1b12635e4ae962d1219aeabf9dd8175b
│  │  ├─ 8a
│  │  │  ├─ 23ea5e63faca5f5846e91a217e6e02b5f2de6f
│  │  │  ├─ 28d2c72518d450c924783a12246b882078929c
│  │  │  └─ fb64f85c4975d930a9c6cb1928ff13cfe255db
│  │  ├─ 8b
│  │  │  ├─ 2dc801f71fbda830e49eaca9be9b3015d32899
│  │  │  ├─ 4b18a5dd70af80a5a52b4cfc94203fec9fae95
│  │  │  ├─ 7429951b389ed0183167ba9fc38dc1a8ce11e5
│  │  │  └─ 999a787dae65f4ead19e4ae61e3c1bc557eed9
│  │  ├─ 8c
│  │  │  ├─ bfc13f00157323fd57072cb73652a51c274355
│  │  │  └─ e302a524d737528776d1bee2abe545f35d5ba9
│  │  ├─ 8d
│  │  │  ├─ 6d80367c9525f20e32c4ead173dd494a3d3ca0
│  │  │  ├─ 6e38b3e7c977d7e1357d146ef2f58010073473
│  │  │  └─ f80ba0a4b7300ffd61ffc0fe10dedcc9596516
│  │  ├─ 8e
│  │  │  └─ a43647014d316a1dafeef0c48898a5270bdefd
│  │  ├─ 8f
│  │  │  ├─ 61303c4c7577c12e0a1d5bab5add6869dfe2be
│  │  │  ├─ ac267fd6cff72fe62fc66d6e4cc50f0c17d098
│  │  │  ├─ c140afbbe87c269ed17ef2be17cdb6d93b6e13
│  │  │  └─ f8e15dbd0b3c28c1e9b4f97e53adcaebc3526e
│  │  ├─ 92
│  │  │  └─ e0a588683b2293f0c761652ab6eea0b344ff16
│  │  ├─ 94
│  │  │  ├─ 3022aa473ad8985a1474f93d178647c425c5f2
│  │  │  └─ f9f8a74ba032f842b735d671cb740b949dafbb
│  │  ├─ 96
│  │  │  └─ e1e8cf8826793279c68d3e138fd35a9a446960
│  │  ├─ 97
│  │  │  └─ 22859167906f66d0b2f3fd07d18a3b0c601528
│  │  ├─ 98
│  │  │  └─ e16bac6bc3a82016b0afefab8eb13e3d4e2f7b
│  │  ├─ 99
│  │  │  └─ 01b7f72666ef0bac025b9a078747b2bb28ee39
│  │  ├─ 9a
│  │  │  └─ e546b0f825c4f1da5bc7c6dff08e32539e4ede
│  │  ├─ 9b
│  │  │  ├─ 1550d30df1edda4e52e1b0bbfdf8b3b7985cda
│  │  │  ├─ 6626f06fda640537102f73d052bdc2afedd17e
│  │  │  └─ 9f6dbad3c44aa2dfb81dc5ecb09a99c97067bf
│  │  ├─ 9c
│  │  │  ├─ 32e96d7df1f11670189e0b141669652bf0f1f9
│  │  │  ├─ 91ccaafce92de12dd6a96e07c1712644f949d7
│  │  │  ├─ a61ea832ebf1de098e3c64331338b80fdfab91
│  │  │  └─ ba9d87519d12bf98c3af4c2b0ba5a03ad66b0a
│  │  ├─ 9d
│  │  │  ├─ 0b3f92714509d38713810ab55a7a218ad1b7db
│  │  │  └─ 9bb8d469ca18f81c0afb6aee4c1c46471578cb
│  │  ├─ 9f
│  │  │  ├─ 868ad79afd8db2e9cc0e76dfaaa84f5947e45b
│  │  │  ├─ 989fa05a679453e3d2edbf32b90fc6f48f5647
│  │  │  └─ b73964b818c12a0d57d789fc7c730556f47f16
│  │  ├─ a0
│  │  │  └─ 38590c1702455e7349dd7d52412df308e324a2
│  │  ├─ a1
│  │  │  ├─ 116e395474d8f7ac8a4bd5a6518f6709decca6
│  │  │  ├─ 2f409d62ca55c9ef8aae2804d4b6660d110fe8
│  │  │  └─ d78d83792c69726e9d1553b4882d924e733fa7
│  │  ├─ a2
│  │  │  ├─ 1fa249574e9a7eacaa6038f2d9f193860a774e
│  │  │  ├─ 5742b8e639019e84bb142374b58256d3e658af
│  │  │  └─ 97c1b068f20fe2072a8bc9ecfef6c30d1ab1b5
│  │  ├─ a4
│  │  │  ├─ 3c659be86a5b4b11e1a4ced1307274a202885a
│  │  │  └─ 69021ff37b58ec119a054bef04539698df9d31
│  │  ├─ a5
│  │  │  └─ 3fe5de566105192f5d0a48bc6d5067a0ad3540
│  │  ├─ a6
│  │  │  └─ 9fda3e8e23b34955e9a8d65ccae2b8fb92ea67
│  │  ├─ a8
│  │  │  ├─ 0128a421e11a941f6b990618f687e482de944f
│  │  │  ├─ 2268aa911eee98270a6e2ca5dbd28e4aef18f2
│  │  │  └─ 457ca7cb0c2eee147f7ee5c0f8fdc080d28525
│  │  ├─ a9
│  │  │  ├─ 615698d52b1ec68797ee14c5fa5f38764a39e5
│  │  │  └─ 697041d1cde37a05f84b815a602f0868d69249
│  │  ├─ aa
│  │  │  └─ 7c9446c117b45cee5d1c3bbe667f3e40268d06
│  │  ├─ ac
│  │  │  ├─ 3057dba4dd2a7349bd6ba9ce0ec7e0aec7e862
│  │  │  └─ a65907bae7f499a70bdf8c9686e82ac7e204ac
│  │  ├─ ad
│  │  │  ├─ 1c9ffee41776930a636d94bea480a1623046bb
│  │  │  └─ acacee6d8eae603ca7bf6c3dbe013c73f029e2
│  │  ├─ ae
│  │  │  └─ c0292d2ddb3b33e6fab238ded0d9cea8b0ccf3
│  │  ├─ b1
│  │  │  ├─ 6a59d7670e8d7fa83705c57c16ef9ec0e3b1e4
│  │  │  ├─ 82363f62586223aa7066148a5916f8d00381bb
│  │  │  ├─ 8f15801e494d675639b146a15cf015262eaf43
│  │  │  ├─ 9a070bc526c19ca4e5db3d9ea595769eddad25
│  │  │  └─ a5af6f0d9a0cb81530bb7cff3b332bf9d9f514
│  │  ├─ b2
│  │  │  ├─ 309f1ec1f1ae2b4e44c537543fbead1daaac14
│  │  │  ├─ 4d8cda87a9455ac2c953f13b55f107e682c577
│  │  │  └─ b3b2aab79be62ed2ab0c3370e68f69de2e4d90
│  │  ├─ b3
│  │  │  ├─ 5f066fb8567d6b12dd63272bde64292b52ca78
│  │  │  └─ bb2610b6dacd314a1b96a5578714cbeaf5ad50
│  │  ├─ b4
│  │  │  └─ 108f1cd7e39fdf9584f3b3513cfe6cc5e6a5d3
│  │  ├─ b5
│  │  │  ├─ b0692b61a1f081f89983e9afb4dc23c5983400
│  │  │  └─ ba153071932f4ad35ae0c22976f2208eb47997
│  │  ├─ b6
│  │  │  └─ b1ad921bd9ea96109d037aca38c3dab72a9383
│  │  ├─ b7
│  │  │  ├─ 3446d1c520276de5860d0ce2c9304021b13f9d
│  │  │  ├─ 46e3668655137cde164e1118ff3f8e9be091c0
│  │  │  ├─ 96531599dabd5cdc0656a062d121a872ba6cd7
│  │  │  └─ a524763e61edbfbf5e503f6c54c0a8c4f6808b
│  │  ├─ b8
│  │  │  ├─ 3207b67836ef56efd883134ba09576135bb4ff
│  │  │  ├─ 76a46e4f7e4a17042297fea46002f2c869370a
│  │  │  └─ 8d5b6633e7e4526133bc151b9ea8f59356dd43
│  │  ├─ b9
│  │  │  ├─ 285ab5ba1901b46024b5bcf784747bca65646f
│  │  │  ├─ bf26d8be1c8040b43047cb2358cb17f0ebdd93
│  │  │  └─ e47a9adc0a449050cc590edb0c396f16bd05ae
│  │  ├─ ba
│  │  │  ├─ 67cc0b5a9afad010b9b343d0f37d4c8320b718
│  │  │  ├─ 81a12b7294d642733dd1e131db4f6a32354850
│  │  │  └─ fbcca71012443f20aaacec7367bda51cac603d
│  │  ├─ bb
│  │  │  ├─ 040c8179ed449b61aa3299baa68a66cdb6e92d
│  │  │  ├─ 0768368b3494747aa028ded2d08b05b6e34e2a
│  │  │  ├─ 09d8c384350e66a373f5eafc41744fbd67f28a
│  │  │  └─ 45627633f0b2808b9a43897d83152be47aa567
│  │  ├─ bc
│  │  │  ├─ 5b4b5c6a18789b070b0d155ca4a0050ca3cb2e
│  │  │  ├─ 71131acd047f33edfa600e263d6c37df255357
│  │  │  ├─ 8584bfa826c349f8391d144ee7cf7342e2ce46
│  │  │  ├─ 92b287b7962cee593ba8aee8ac89735dfcd805
│  │  │  ├─ c3302924f1fe4108a6ef59642e29f106eb8b11
│  │  │  └─ fd737238ce3a5df804f410ade8c91a8918786d
│  │  ├─ bd
│  │  │  ├─ cf3c0b3875d1f32c64c04a90845372a93363e9
│  │  │  └─ e5282d986f14a8d080bed83d16605f76e4a721
│  │  ├─ be
│  │  │  ├─ 13ac8670f7766eea471cf6ceecaba0a0a5e6fe
│  │  │  ├─ 7a4bf1f69963d79c97a8685e06f89e47684785
│  │  │  └─ b1e6afa91c54b03993624cc924c7c8c3d0be68
│  │  ├─ bf
│  │  │  ├─ 46344496278634e9d8f3d51de20b93108286a8
│  │  │  ├─ 4d901dc9f246e5e19bc313481bee77076b5d0f
│  │  │  └─ 87b613d6a7039da0c3047f3419f64a060b24e0
│  │  ├─ c0
│  │  │  ├─ 959e3ce8b88f42c23bd1ca15fa2a727f35f8a2
│  │  │  ├─ a1ff446706054c24dfc46609025fcb66c54925
│  │  │  └─ d90d447af3f9e539b1955d1dd806774268441b
│  │  ├─ c1
│  │  │  └─ f6b1bc9f09bf9ed9de61294e4b002b8adbfe9f
│  │  ├─ c3
│  │  │  ├─ 387a929925cd5a41f1e69ec4da4edc623eb3d2
│  │  │  └─ dc07299db4c6d9589dafe0be400a576fe4d80b
│  │  ├─ c4
│  │  │  └─ e38fb223f97373581bfce4dc1ecb61da1a7260
│  │  ├─ c6
│  │  │  ├─ 19a3031a41352a14f50c635f386b0081dafabb
│  │  │  └─ 9dfeac175b864eeb88adb6588c18d4375ddfc6
│  │  ├─ c7
│  │  │  ├─ 1a2bf62144e7952814fb2caf16578982852366
│  │  │  ├─ 2afce4000e14f761cefabbd43dbe62bbc04ec3
│  │  │  └─ 7341ae721a459deb1acdea719ed4347b145784
│  │  ├─ c8
│  │  │  ├─ 1e97dcb9f5cc64dca2de69235576ee2e5e3b2f
│  │  │  ├─ 5269bbd2066bf878f7f2c467d25df27000ead2
│  │  │  └─ 806c17de4a34946316633d06fd8a1c19c1ef4c
│  │  ├─ c9
│  │  │  ├─ 2eb0b4d79b3da861c4c9a99da020bddaaff785
│  │  │  └─ 59c70564cad8b5e0ecb6c4dcb5d8baeedb40b1
│  │  ├─ cb
│  │  │  ├─ 5f1c8bb29f9f66db89d83f32e6ad0806a31682
│  │  │  ├─ 61bdc17970470df1b924824ead9b3866b956c8
│  │  │  └─ 9248f3b70af168be7ce8ce602d6fe8fab7735b
│  │  ├─ cd
│  │  │  └─ ef6ba653ab9ed305619b2d80580d2397bab3d8
│  │  ├─ ce
│  │  │  ├─ 409cd223c2fd467eb0a69c7c53d531c8c8d955
│  │  │  ├─ 77cc7d51c3f4cf3b8e151aa9ebda5427053a13
│  │  │  └─ cbb8f6960a30ea3fa4764e1fdb48f9bb10ecb5
│  │  ├─ cf
│  │  │  ├─ 785d91fe571900e2c81d5fc72b657460505e83
│  │  │  └─ c23e5da983fa7d52ea1d0f4ff3cddcae08e7c2
│  │  ├─ d0
│  │  │  ├─ 17d3d2eaacc083154dba4487290eb4f5d10114
│  │  │  ├─ 2c38a55267edd0d8f75e9b5cf3c2867c080e59
│  │  │  └─ bd54bcb772fd2d54b4415833877ae036dcb737
│  │  ├─ d1
│  │  │  ├─ 290bf7a8f9e843e3501ccb7b18c81b92900312
│  │  │  ├─ 72ed892f32123e2fd3c902c4c8d195a56611b1
│  │  │  └─ eb4c1a7c444c7a254991a67d6b9a237a1bd7be
│  │  ├─ d2
│  │  │  ├─ 44463f80e1755a5a8ef2ca2b18f1abed000231
│  │  │  ├─ d1f5c19a881a0490eac591bb34b5b66ad04307
│  │  │  ├─ def1a05530f97c201e2259c50152ddbef4eec5
│  │  │  ├─ f3ec95d586fb91278f470c0563362ebc24a908
│  │  │  └─ fe3d74554f0a6ccdb93d8d6de44150e621bddb
│  │  ├─ d3
│  │  │  ├─ c638fa9986d5da432160c200df007658b6365d
│  │  │  └─ e22ecfe24fd69d2b8913fcedc2faf5c5b48f7f
│  │  ├─ d4
│  │  │  └─ 9e7a0bdfd0e919d01ff3511f2bdb908be3a864
│  │  ├─ d6
│  │  │  ├─ 46b38c7b719d2f4be673fc96e9420a7a609fed
│  │  │  └─ 582f5cfcadfc6700989292af8fd8e6753cd324
│  │  ├─ d7
│  │  │  ├─ 238dd0cb607d2aa2208671c8393dbd669d396d
│  │  │  └─ 92866bfe052304e9fb6b3c6c3e390fb3e3fc99
│  │  ├─ d9
│  │  │  └─ 5e610c7d0d5b1d804057f792556cfae7324a60
│  │  ├─ da
│  │  │  ├─ 31d2ae0f4f1c820050751a47eebcac607f8983
│  │  │  ├─ 7b822bf8b96f10f600bb1201c876c8fcbf9510
│  │  │  ├─ 86963c11a6813f3a988e2cb12210f59a7d6b8f
│  │  │  ├─ ae222afa4c7444be6c78b60cdcbfce4a9bd3cd
│  │  │  └─ cec7425e1fbb284ff32cc0f8d6e3e108da2d06
│  │  ├─ db
│  │  │  ├─ 2bbb136e3477c335487c87d0f8fa32df1ef045
│  │  │  └─ 6b99b86a77f024ffefe248590a952d567303bd
│  │  ├─ dc
│  │  │  ├─ 264c8c086048bc6886367434afb8cd34299589
│  │  │  ├─ 58c09875a4f71fa48c16cc30c199e343152f95
│  │  │  └─ 8cb7f177888a5e4cd079cd33aaa4b410a945f7
│  │  ├─ dd
│  │  │  ├─ 0c7e986b0524a0c50639ba4ef442416271c798
│  │  │  ├─ 50f844475cca615a5bc1aaf4611f9e527cda6d
│  │  │  └─ 62cb92bb255593870da7494218e0dfe8ec0bc9
│  │  ├─ de
│  │  │  ├─ 5125b43129e41883694310127f159b00715f18
│  │  │  ├─ 585837faac14d7a1d3952ad675f33fff990bb1
│  │  │  └─ 91c2d87c931d992d0f6a40eed377dc7ade2c23
│  │  ├─ df
│  │  │  ├─ 8d794d5ff699b33fbaad66a48499edc6251f9e
│  │  │  └─ a37aba1fedf2bf223de05c26aebcf8e8a7d999
│  │  ├─ e0
│  │  │  └─ e995d1e7ecd9e1fd179a8785f612f1592f1860
│  │  ├─ e1
│  │  │  ├─ b161733745db7a010be900450fa637138440c9
│  │  │  └─ ea22f0b7aba1d62b368602880a145a86680bd5
│  │  ├─ e2
│  │  │  └─ 71d9d2dba75113de1e912a8dfeac636c4c90b4
│  │  ├─ e6
│  │  │  ├─ 991887b55f1772505263dd700cec1bcb918467
│  │  │  ├─ 9de29bb2d1d6434b8b29ae775ad8c2e48c5391
│  │  │  ├─ b8f235a813bbe60710ee6fc5bb6eba022d31cb
│  │  │  └─ f3f75e483779408c9f87bdc612ddb9c9f9141e
│  │  ├─ e7
│  │  │  ├─ 76c572df16592f445d4161faa304307e765936
│  │  │  ├─ 9d396a5ecdb07e6d0e7bb076131208fd9163e7
│  │  │  └─ fb67d45bbebd04bbac5bc7b87c8bbf57e36020
│  │  ├─ e8
│  │  │  ├─ 4a59c0fdab42ff414421e689035ac5d478aeaf
│  │  │  ├─ 66d177d9f6a0519d658dd91b461a5a69c6203d
│  │  │  └─ e59d7b1027926872bc3586baa95d593cced856
│  │  ├─ e9
│  │  │  └─ 719ab689c3ab49009dc127f021fe5c7760eaa9
│  │  ├─ ea
│  │  │  ├─ 0e9407aa373624bf2ca68e00dea14ee4fb794a
│  │  │  ├─ 4bbcfa2896a1a30f25e2f9a740523e035bce08
│  │  │  └─ d1400dd8c1fbc5ff033974f23fe07ad0787ece
│  │  ├─ eb
│  │  │  ├─ 1ebb4fa4df303dc279d8035da451a797633c8e
│  │  │  ├─ 1fab25445fe2b03f87b413b889dc684a3a78cd
│  │  │  └─ 5eac4db878c547be640b6606fe20aef2508e3a
│  │  ├─ ec
│  │  │  ├─ 6707776bba8702d2860405d7c255a188629878
│  │  │  ├─ ae5cd21a958878a3484301e279717969a2312b
│  │  │  └─ fcd106688a5e1b7cac4f156fb419c22ff0b925
│  │  ├─ ee
│  │  │  ├─ eba7ec849976a7e75a84e006e41aaa4668b777
│  │  │  └─ fb9cac75acaf7374a359f64ae603ed1ea9cc43
│  │  ├─ ef
│  │  │  └─ 354f614fae9f06520913f80b6f9174a09e5993
│  │  ├─ f1
│  │  │  ├─ 6a072248f1f299a16620ea018f91389d874618
│  │  │  ├─ d51713708948816c3151355b3463f63aef7324
│  │  │  ├─ df7228ed17b8f33b713f9c0a5e47fc40542144
│  │  │  └─ e9796a5a0a06f594f78f7d1f5dbd490611426c
│  │  ├─ f2
│  │  │  └─ 962d3e4d1b53b7202297e01a97467b430bacc3
│  │  ├─ f3
│  │  │  ├─ 34840c15f178561fb5f50b4bb1db3fd2ece04e
│  │  │  └─ e5ca79f7d6f579fa468a0e4838f9984369d5d6
│  │  ├─ f4
│  │  │  └─ dc95a55cc94e764172d9fcc8a8729fa0cea60a
│  │  ├─ f5
│  │  │  ├─ 6a7d48b058440aa0431c6ee7ffa8627ae48a5b
│  │  │  ├─ ed35af5a6e02666c1746239b94029c120cee49
│  │  │  └─ f1e98bff5873d78b8b0cd72d5bf58fe318c2fb
│  │  ├─ f6
│  │  │  ├─ 0aa4cc7c40a19a6d3f103620252080c02bce36
│  │  │  ├─ bf036c30a921cf12255b2bf93b3bf49918550d
│  │  │  ├─ bfc2ceaf9186ac40a1eb3db4349c10303897d6
│  │  │  └─ c5537785efa086c20c8c174cb04a2892142c59
│  │  ├─ f7
│  │  │  └─ 1bf3c3d0220e4e762ef43057110c12d62d04ef
│  │  ├─ f8
│  │  │  ├─ 52e342d0cdd23a4ec13abeaaa1d00db40239f6
│  │  │  └─ 68a65733f755347fa5d8a78a389ba5c0b51378
│  │  ├─ f9
│  │  │  └─ 7e582057602d76c9f4cbdf4e8d97fc03518208
│  │  ├─ fa
│  │  │  └─ ffa94439d0c51ed5fde6538a32a25337e55fb6
│  │  ├─ fb
│  │  │  ├─ 019728489436e52af8877b79481f199911a976
│  │  │  └─ d8ba36390cf70486f5127d7b0e0e72c4436521
│  │  ├─ fc
│  │  │  ├─ 1432b994ed4d5dfdded1297babd7dbdd421896
│  │  │  └─ 7781d1c5f4a1db729de7a24e0319ccd39f6a80
│  │  ├─ fd
│  │  │  └─ 08ae55877daddc97306b55ecd2eaac14b90f62
│  │  ├─ fe
│  │  │  ├─ 5990c50d9e8dd13d9aada41c0e56a6226623cd
│  │  │  └─ fd44e242b9fe16858c4f8ee0166d1b611ee962
│  │  ├─ ff
│  │  │  ├─ 137f4d1e5b611d6ecef4c50840fdb8edbffdaa
│  │  │  ├─ 3c26cb86d5e7b5cb86c7d9556b546906b55aeb
│  │  │  └─ 93ddb52cbb3184ab4c824dc8d124a37f01988a
│  │  ├─ info
│  │  └─ pack
│  │     ├─ pack-c334a3472e5e41be4dac965bed8e6aa7263da6df.idx
│  │     └─ pack-c334a3472e5e41be4dac965bed8e6aa7263da6df.pack
│  ├─ packed-refs
│  └─ refs
│     ├─ heads
│     │  └─ main
│     ├─ remotes
│     │  └─ origin
│     │     ├─ HEAD
│     │     └─ main
│     └─ tags
├─ .gitignore
├─ CMakeLists.txt
├─ README.md
├─ data
├─ depends
│  ├─ googletest
│  │  ├─ .clang-format
│  │  ├─ BUILD.bazel
│  │  ├─ CMakeLists.txt
│  │  ├─ CONTRIBUTING.md
│  │  ├─ CONTRIBUTORS
│  │  ├─ LICENSE
│  │  ├─ README.md
│  │  ├─ WORKSPACE
│  │  ├─ ci
│  │  │  ├─ linux-presubmit.sh
│  │  │  ├─ macos-presubmit.sh
│  │  │  └─ windows-presubmit.bat
│  │  ├─ docs
│  │  │  ├─ _config.yml
│  │  │  ├─ _data
│  │  │  │  └─ navigation.yml
│  │  │  ├─ _layouts
│  │  │  │  └─ default.html
│  │  │  ├─ _sass
│  │  │  │  └─ main.scss
│  │  │  ├─ advanced.md
│  │  │  ├─ assets
│  │  │  │  └─ css
│  │  │  │     └─ style.scss
│  │  │  ├─ community_created_documentation.md
│  │  │  ├─ faq.md
│  │  │  ├─ gmock_cheat_sheet.md
│  │  │  ├─ gmock_cook_book.md
│  │  │  ├─ gmock_faq.md
│  │  │  ├─ gmock_for_dummies.md
│  │  │  ├─ index.md
│  │  │  ├─ pkgconfig.md
│  │  │  ├─ platforms.md
│  │  │  ├─ primer.md
│  │  │  ├─ quickstart-bazel.md
│  │  │  ├─ quickstart-cmake.md
│  │  │  ├─ reference
│  │  │  │  ├─ actions.md
│  │  │  │  ├─ assertions.md
│  │  │  │  ├─ matchers.md
│  │  │  │  ├─ mocking.md
│  │  │  │  └─ testing.md
│  │  │  └─ samples.md
│  │  ├─ googlemock
│  │  │  ├─ CMakeLists.txt
│  │  │  ├─ README.md
│  │  │  ├─ cmake
│  │  │  │  ├─ gmock.pc.in
│  │  │  │  └─ gmock_main.pc.in
│  │  │  ├─ docs
│  │  │  │  └─ README.md
│  │  │  ├─ include
│  │  │  │  └─ gmock
│  │  │  │     ├─ gmock-actions.h
│  │  │  │     ├─ gmock-cardinalities.h
│  │  │  │     ├─ gmock-function-mocker.h
│  │  │  │     ├─ gmock-matchers.h
│  │  │  │     ├─ gmock-more-actions.h
│  │  │  │     ├─ gmock-more-matchers.h
│  │  │  │     ├─ gmock-nice-strict.h
│  │  │  │     ├─ gmock-spec-builders.h
│  │  │  │     ├─ gmock.h
│  │  │  │     └─ internal
│  │  │  │        ├─ custom
│  │  │  │        │  ├─ README.md
│  │  │  │        │  ├─ gmock-generated-actions.h
│  │  │  │        │  ├─ gmock-matchers.h
│  │  │  │        │  └─ gmock-port.h
│  │  │  │        ├─ gmock-internal-utils.h
│  │  │  │        ├─ gmock-port.h
│  │  │  │        └─ gmock-pp.h
│  │  │  ├─ src
│  │  │  │  ├─ gmock-all.cc
│  │  │  │  ├─ gmock-cardinalities.cc
│  │  │  │  ├─ gmock-internal-utils.cc
│  │  │  │  ├─ gmock-matchers.cc
│  │  │  │  ├─ gmock-spec-builders.cc
│  │  │  │  ├─ gmock.cc
│  │  │  │  └─ gmock_main.cc
│  │  │  └─ test
│  │  │     ├─ BUILD.bazel
│  │  │     ├─ gmock-actions_test.cc
│  │  │     ├─ gmock-cardinalities_test.cc
│  │  │     ├─ gmock-function-mocker_test.cc
│  │  │     ├─ gmock-internal-utils_test.cc
│  │  │     ├─ gmock-matchers-arithmetic_test.cc
│  │  │     ├─ gmock-matchers-comparisons_test.cc
│  │  │     ├─ gmock-matchers-containers_test.cc
│  │  │     ├─ gmock-matchers-misc_test.cc
│  │  │     ├─ gmock-matchers_test.h
│  │  │     ├─ gmock-more-actions_test.cc
│  │  │     ├─ gmock-nice-strict_test.cc
│  │  │     ├─ gmock-port_test.cc
│  │  │     ├─ gmock-pp-string_test.cc
│  │  │     ├─ gmock-pp_test.cc
│  │  │     ├─ gmock-spec-builders_test.cc
│  │  │     ├─ gmock_all_test.cc
│  │  │     ├─ gmock_ex_test.cc
│  │  │     ├─ gmock_leak_test.py
│  │  │     ├─ gmock_leak_test_.cc
│  │  │     ├─ gmock_link2_test.cc
│  │  │     ├─ gmock_link_test.cc
│  │  │     ├─ gmock_link_test.h
│  │  │     ├─ gmock_output_test.py
│  │  │     ├─ gmock_output_test_.cc
│  │  │     ├─ gmock_output_test_golden.txt
│  │  │     ├─ gmock_stress_test.cc
│  │  │     ├─ gmock_test.cc
│  │  │     └─ gmock_test_utils.py
│  │  └─ googletest
│  │     ├─ CMakeLists.txt
│  │     ├─ README.md
│  │     ├─ cmake
│  │     │  ├─ Config.cmake.in
│  │     │  ├─ gtest.pc.in
│  │     │  ├─ gtest_main.pc.in
│  │     │  ├─ internal_utils.cmake
│  │     │  └─ libgtest.la.in
│  │     ├─ docs
│  │     │  └─ README.md
│  │     ├─ include
│  │     │  └─ gtest
│  │     │     ├─ gtest-assertion-result.h
│  │     │     ├─ gtest-death-test.h
│  │     │     ├─ gtest-matchers.h
│  │     │     ├─ gtest-message.h
│  │     │     ├─ gtest-param-test.h
│  │     │     ├─ gtest-printers.h
│  │     │     ├─ gtest-spi.h
│  │     │     ├─ gtest-test-part.h
│  │     │     ├─ gtest-typed-test.h
│  │     │     ├─ gtest.h
│  │     │     ├─ gtest_pred_impl.h
│  │     │     ├─ gtest_prod.h
│  │     │     └─ internal
│  │     │        ├─ custom
│  │     │        │  ├─ README.md
│  │     │        │  ├─ gtest-port.h
│  │     │        │  ├─ gtest-printers.h
│  │     │        │  └─ gtest.h
│  │     │        ├─ gtest-death-test-internal.h
│  │     │        ├─ gtest-filepath.h
│  │     │        ├─ gtest-internal.h
│  │     │        ├─ gtest-param-util.h
│  │     │        ├─ gtest-port-arch.h
│  │     │        ├─ gtest-port.h
│  │     │        ├─ gtest-string.h
│  │     │        └─ gtest-type-util.h
│  │     ├─ src
│  │     │  ├─ gtest-all.cc
│  │     │  ├─ gtest-assertion-result.cc
│  │     │  ├─ gtest-death-test.cc
│  │     │  ├─ gtest-filepath.cc
│  │     │  ├─ gtest-internal-inl.h
│  │     │  ├─ gtest-matchers.cc
│  │     │  ├─ gtest-port.cc
│  │     │  ├─ gtest-printers.cc
│  │     │  ├─ gtest-test-part.cc
│  │     │  ├─ gtest-typed-test.cc
│  │     │  ├─ gtest.cc
│  │     │  └─ gtest_main.cc
│  │     └─ test
│  │        ├─ BUILD.bazel
│  │        ├─ googletest-break-on-failure-unittest.py
│  │        ├─ googletest-break-on-failure-unittest_.cc
│  │        ├─ googletest-catch-exceptions-test.py
│  │        ├─ googletest-catch-exceptions-test_.cc
│  │        ├─ googletest-color-test.py
│  │        ├─ googletest-color-test_.cc
│  │        ├─ googletest-death-test-test.cc
│  │        ├─ googletest-death-test_ex_test.cc
│  │        ├─ googletest-env-var-test.py
│  │        ├─ googletest-env-var-test_.cc
│  │        ├─ googletest-failfast-unittest.py
│  │        ├─ googletest-failfast-unittest_.cc
│  │        ├─ googletest-filepath-test.cc
│  │        ├─ googletest-filter-unittest.py
│  │        ├─ googletest-filter-unittest_.cc
│  │        ├─ googletest-global-environment-unittest.py
│  │        ├─ googletest-global-environment-unittest_.cc
│  │        ├─ googletest-json-outfiles-test.py
│  │        ├─ googletest-json-output-unittest.py
│  │        ├─ googletest-list-tests-unittest.py
│  │        ├─ googletest-list-tests-unittest_.cc
│  │        ├─ googletest-listener-test.cc
│  │        ├─ googletest-message-test.cc
│  │        ├─ googletest-options-test.cc
│  │        ├─ googletest-output-test-golden-lin.txt
│  │        ├─ googletest-output-test.py
│  │        ├─ googletest-output-test_.cc
│  │        ├─ googletest-param-test-invalid-name1-test.py
│  │        ├─ googletest-param-test-invalid-name1-test_.cc
│  │        ├─ googletest-param-test-invalid-name2-test.py
│  │        ├─ googletest-param-test-invalid-name2-test_.cc
│  │        ├─ googletest-param-test-test.cc
│  │        ├─ googletest-param-test-test.h
│  │        ├─ googletest-param-test2-test.cc
│  │        ├─ googletest-port-test.cc
│  │        ├─ googletest-printers-test.cc
│  │        ├─ googletest-setuptestsuite-test.py
│  │        ├─ googletest-setuptestsuite-test_.cc
│  │        ├─ googletest-shuffle-test.py
│  │        ├─ googletest-shuffle-test_.cc
│  │        ├─ googletest-test-part-test.cc
│  │        ├─ googletest-throw-on-failure-test.py
│  │        ├─ googletest-throw-on-failure-test_.cc
│  │        ├─ googletest-uninitialized-test.py
│  │        ├─ googletest-uninitialized-test_.cc
│  │        ├─ gtest-typed-test2_test.cc
│  │        ├─ gtest-typed-test_test.cc
│  │        ├─ gtest-typed-test_test.h
│  │        ├─ gtest-unittest-api_test.cc
│  │        ├─ gtest_all_test.cc
│  │        ├─ gtest_assert_by_exception_test.cc
│  │        ├─ gtest_dirs_test.cc
│  │        ├─ gtest_environment_test.cc
│  │        ├─ gtest_help_test.py
│  │        ├─ gtest_help_test_.cc
│  │        ├─ gtest_json_test_utils.py
│  │        ├─ gtest_list_output_unittest.py
│  │        ├─ gtest_list_output_unittest_.cc
│  │        ├─ gtest_main_unittest.cc
│  │        ├─ gtest_no_test_unittest.cc
│  │        ├─ gtest_pred_impl_unittest.cc
│  │        ├─ gtest_premature_exit_test.cc
│  │        ├─ gtest_prod_test.cc
│  │        ├─ gtest_repeat_test.cc
│  │        ├─ gtest_skip_check_output_test.py
│  │        ├─ gtest_skip_environment_check_output_test.py
│  │        ├─ gtest_skip_in_environment_setup_test.cc
│  │        ├─ gtest_skip_test.cc
│  │        ├─ gtest_sole_header_test.cc
│  │        ├─ gtest_stress_test.cc
│  │        ├─ gtest_test_macro_stack_footprint_test.cc
│  │        ├─ gtest_test_utils.py
│  │        ├─ gtest_testbridge_test.py
│  │        ├─ gtest_testbridge_test_.cc
│  │        ├─ gtest_throw_on_failure_ex_test.cc
│  │        ├─ gtest_unittest.cc
│  │        ├─ gtest_xml_outfile1_test_.cc
│  │        ├─ gtest_xml_outfile2_test_.cc
│  │        ├─ gtest_xml_outfiles_test.py
│  │        ├─ gtest_xml_output_unittest.py
│  │        ├─ gtest_xml_output_unittest_.cc
│  │        ├─ gtest_xml_test_utils.py
│  │        ├─ production.cc
│  │        └─ production.h
│  └─ libull
│     ├─ include
│     │  └─ ull.h
│     └─ src
│        └─ main.cpp
├─ docs
│  ├─ README.md
│  ├─ bonus.md
│  └─ requirements.md
├─ scripts
│  └─ build.sh
├─ src
│  ├─ Book
│  │  └─ BookSystem.h
│  ├─ Bookstore.cc
│  ├─ Bookstore.h
│  ├─ CMakeLists.txt
│  ├─ Exception.cc
│  ├─ Exception.h
│  ├─ User
│  │  ├─ BookstoreBaseUser.h
│  │  ├─ BookstoreManager.h
│  │  └─ UserSystem.h
│  ├─ main.cc
│  ├─ utils.cc
│  └─ utils.h
└─ test
   ├─ CMakeLists.txt
   └─ test.cc

```