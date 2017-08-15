# -------------------------------------------------
# Project created by QtCreator 2013-08-15T10:15:26
# -------------------------------------------------
#QT += qt3support
TARGET = hmisvr
TEMPLATE = app
SOURCES += main.cpp \
    main_dialog.cpp \
    p01_passwd_dialog.cpp \
   p02_servchoose_dialog.cpp \
   p03_historyquery_dialog.cpp \
    p05_chargelink_dialog.cpp \
    #p06_chargeconfigrm_dialog.cpp \
    p07_chargetypechoose_dialog.cpp \
    p08_chargebytime_dialog.cpp \
    p09_chargebyenergy_dialog.cpp \
    #p10_chargebyauto_dialog.cpp \
    #p11_charging_dialog.cpp \
    #p12_payoff_dialog.cpp \
    globalhmi.cpp \
    p13_setpara_dialog.cpp \
    p14_setpara_sub1_dialog.cpp \
    p15_setpara_sub2_dialog.cpp \
    p16_setpara_sub3_dialog.cpp \
    p17_setpara_sub4_dialog.cpp \
    p19_charging_dialog.cpp \
    p20_payoff_dialog.cpp \
    dialog_1.cpp \
    dialog_2.cpp \
    #p22_elecprice_dialog.cpp \
    #p21_leftmoney_dialog.cpp \
    #p18_setpara_sub5_dialog.cpp \
    #p23_chargebymoney.cpp \
    p24_setpara_sub6_dialog.cpp \
    p21_judge_continue.cpp \
    dialog_error.cpp \
    dialog_end.cpp \
    #dialog_order.cpp \
    dialog_book.cpp \
    dialog_checkcaed.cpp \
    dialog_back.cpp \
    dialog_link_err.cpp \
    dialog_diff_card.cpp \
    dialog_pull_gun.cpp \
    dialog_money_left.cpp \
    dialog_history_net.cpp \
    dialog_first_err.cpp \
    dialog_history_choose.cpp \
    dialog_passwd_app.cpp \
    dialog_carnum.cpp \
    dialog_order.cpp \
    p06_chargeconfigrm_dialog.cpp \
    dialog_err_carconfirm.cpp \
    dialog_not_putiancard.cpp \
    p18_setpara_sub5_dialog.cpp \
    dialog_err_choose.cpp \
    dialog_local_err.cpp \
    dialog_remote_err.cpp

HEADERS += main_dialog.h \
    p01_passwd_dialog.h \
    p02_servchoose_dialog.h \
    p03_historyquery_dialog.h \
    p05_chargelink_dialog.h \
    #p06_chargeconfigrm_dialog.h \
    p07_chargetypechoose_dialog.h \
    p08_chargebytime_dialog.h \
    p09_chargebyenergy_dialog.h \
    #p10_chargebyauto_dialog.h \
    #p11_charging_dialog.h \
    #p12_payoff_dialog.h \
    globalhmi.h \
    p13_setpara_dialog.h \
    p14_setpara_sub1_dialog.h \
    p15_setpara_sub2_dialog.h \
    p16_setpara_sub3_dialog.h \
    p17_setpara_sub4_dialog.h \
    p19_charging_dialog.h \
    p20_payoff_dialog.h \
    $(PUTIANAC_NEW_INC_RUNTIME_DIR)/inifile.h \
    $(PUTIANAC_NEW_INC_RUNTIME_DIR)/gui.h \
    $(PUTIANAC_NEW_INC_RUNTIME_DIR)/ioremap.h \
    $(PUTIANAC_NEW_INC_RUNTIME_DIR)/DB_Unity.h \
    dialog_1.h \
    dialog_2.h \
    #p22_elecprice_dialog.h \
    #p21_leftmoney_dialog.h \
    #p18_setpara_sub5_dialog.h \
    #p23_chargebymoney.h \
    p24_setpara_sub6_dialog.h \
    p21_judge_continue.h \
    dialog_error.h \
    dialog_end.h \
    #dialog_order.h \
    dialog_book.h \
    dialog_checkcaed.h \
    dialog_back.h \
    dialog_link_err.h \
    dialog_diff_card.h \
    dialog_pull_gun.h \
    dialog_money_left.h \
    dialog_history_net.h \
    dialog_first_err.h \
    dialog_history_choose.h \
    dialog_passwd_app.h \
    dialog_carnum.h \
    dialog_order.h \
    p06_chargeconfigrm_dialog.h \
    dialog_err_carconfirm.h \
    dialog_not_putiancard.h \
    p18_setpara_sub5_dialog.h \
    dialog_err_choose.h \
    dialog_local_err.h \
    dialog_remote_err.h

FORMS += main_dialog.ui \
    p01_passwd_dialog.ui \
   p02_servchoose_dialog.ui \
   p03_historyquery_dialog.ui \
    p05_chargelink_dialog.ui \
    #p06_chargeconfigrm_dialog.ui \
    p07_chargetypechoose_dialog.ui \
    p08_chargebytime_dialog.ui \
    p09_chargebyenergy_dialog.ui \
    #p10_chargebyauto_dialog.ui \
    #p11_charging_dialog.ui \
    #p12_payoff_dialog.ui \
    p13_setpara_dialog.ui \
    p14_setpara_sub1_dialog.ui \
    p15_setpara_sub2_dialog.ui \
    p16_setpara_sub3_dialog.ui \
    p17_setpara_sub4_dialog.ui \
    p19_charging_dialog.ui \
    p20_payoff_dialog.ui \
    #dialog_1.ui \
    dialog_2.ui \
    #p22_elecprice_dialog.ui \
    #p21_leftmoney_dialog.ui \
    #p18_setpara_sub5_dialog.ui \
    #p23_chargebymoney.ui \
    p24_setpara_sub6_dialog.ui \
    p21_judge_continue.ui \
    dialog_error.ui \
    dialog_end.ui \
    #dialog_order.ui \
    dialog_book.ui \
    dialog_checkcaed.ui \
    dialog_back.ui \
    dialog_link_err.ui \
    dialog_diff_card.ui \
    dialog_pull_gun.ui \
    dialog_money_left.ui \
    dialog_history_net.ui \
    dialog_first_err.ui \
    dialog_history_choose.ui \
    dialog_passwd_app.ui \
    dialog_carnum.ui \
    dialog_1.ui \
    p06_chargeconfigrm_dialog.ui \
    dialog_order.ui \
    dialog_err_carconfirm.ui \
    dialog_not_putiancard.ui \
    p18_setpara_sub5_dialog.ui \
    dialog_err_choose.ui \
    dialog_local_err.ui \
    dialog_remote_err.ui
RESOURCES += hmisvr.qrc
#INCLUDEPATH += /usr/local/qwt-arm/include \
INCLUDEPATH += $(PUTIANAC_NEW_INC_RUNTIME_DIR)
#LIBS += -L"/usr/local/qwt-arm/lib" \
LIBS += -L $(PUTIANAC_NEW_LIB_RUNTIME_DIR)\
    -lsem \
    -linireadwrite \
    -ldl
