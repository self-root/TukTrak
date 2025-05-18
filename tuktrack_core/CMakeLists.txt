cmake_minimum_required(VERSION 3.16)

project(tuktrack_core LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core)
find_package(Qt6 REQUIRED COMPONENTS Sql)

add_library(tuktrack_core SHARED
    tuktrack_core_global.h
    corecontroller.cpp
    corecontroller.h
    utils.h utils.cpp
    data/databaseaccessmanager.h data/databaseaccessmanager.cpp
    data/tuktuk.h data/tuktuk.cpp
    data/tuktukdao.h data/tuktukdao.cpp
    models/tuktuklistmodel.h models/tuktuklistmodel.cpp
    data/tukdriver.h data/tukdriver.cpp
    data/tukdriverdao.h data/tukdriverdao.cpp
    models/driverslistmodel.h models/driverslistmodel.cpp
    models/driverdetailmodel.h models/driverdetailmodel.cpp
    data/tukdriversetting.h data/tukdriversetting.cpp
    data/driverdepositsetting.h data/driverdepositsetting.cpp
    data/driverdepositdao.h data/driverdepositdao.cpp
    models/driverdepositsettingmodel.h models/driverdepositsettingmodel.cpp
    data/driverdeposit.h data/driverdeposit.cpp
    models/driverdepositmodel.h models/driverdepositmodel.cpp
    models/dashboardmodel.h models/dashboardmodel.cpp
    data/tukmaintenance.h data/tukmaintenance.cpp
    data/maintenancedao.h data/maintenancedao.cpp
    models/tukdetailmodel.h models/tukdetailmodel.cpp
    models/tukdrivershiftmodel.h models/tukdrivershiftmodel.cpp
    models/maintenancelistmodel.h models/maintenancelistmodel.cpp
    models/revenuechartmodel.h models/revenuechartmodel.cpp
    androidapi.h androidapi.cpp
    models/maintenancetypemodel.h models/maintenancetypemodel.cpp
    models/dailydepositlistmodel.h models/dailydepositlistmodel.cpp
    models/depositdatelistmodel.h models/depositdatelistmodel.cpp
    models/dailydepositmodels.h models/dailydepositmodels.cpp
    maintenancerecordcontroller.h maintenancerecordcontroller.cpp
    models/detailedmaintenancelistmodel.h models/detailedmaintenancelistmodel.cpp
    models/maintenancecostbytukmodel.h models/maintenancecostbytukmodel.cpp
    models/maintenancecostbytypemodel.h models/maintenancecostbytypemodel.cpp



)

target_include_directories(tuktrack_core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(tuktrack_core PRIVATE Qt${QT_VERSION_MAJOR}::Core)

target_link_libraries(tuktrack_core PRIVATE Qt6::Sql)

target_compile_definitions(tuktrack_core PRIVATE TUKTRACK_CORE_LIBRARY)
