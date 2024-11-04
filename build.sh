#!/bin/bash

RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m'

VCPKG_PATH_FILE=".vcpkg_path"

show_help() {
    echo -e "${BLUE}Usage: ./build.sh [rule]${NC}"
    echo "Rules:"
    echo -e "  ${YELLOW}setup_vcpkg${NC} - Setup vcpkg"
    echo -e "  ${YELLOW}init${NC}        - Initialize build directory and setup CMake"
    echo -e "  ${YELLOW}reset${NC}       - Delete build directory and reinitialize"
    echo -e "  ${YELLOW}release${NC}     - Configure CMake in Release mode"
    echo -e "  ${YELLOW}debug${NC}       - Configure CMake in Debug mode"
    echo -e "  ${YELLOW}build${NC}       - Build the project"
    echo -e "  ${YELLOW}test${NC}        - Test the project"
    echo -e "  ${YELLOW}lint${NC}        - Run Clang-Tidy on the project"
    echo -e "  ${YELLOW}help${NC}        - Show this help message"
    echo -e "  ${YELLOW}clean${NC}       - Clean binaries, testing folder, and Debug folders"
    echo -e "  ${YELLOW}full_build${NC}  - Run setup_vcpkg, init, release, and build in sequence"
}

check_vcpkg_setup() {
    if [ ! -f "$VCPKG_PATH_FILE" ]; then
        echo -e "${RED}Error: vcpkg path not set. Please run './build.sh setup_vcpkg' first.${NC}"
        exit 1
    fi
}

setup_vcpkg() {
    echo -e "${BLUE}Starting vcpkg setup...${NC}"
    if [ ! -d "vcpkg" ]; then
        echo -e "${YELLOW}vcpkg directory not found. Cloning vcpkg...${NC}"
        git clone https://github.com/microsoft/vcpkg.git
        if [ $? -ne 0 ]; then
            echo -e "${RED}Error: Failed to clone vcpkg repository.${NC}"
            exit 1
        fi
    fi

    vcpkg_cmake_path="vcpkg/scripts/buildsystems/vcpkg.cmake"

    if [ -f "$vcpkg_cmake_path" ]; then
        echo "$vcpkg_cmake_path" > "$VCPKG_PATH_FILE"
        echo -e "${GREEN}vcpkg path set successfully to: ${vcpkg_cmake_path}${NC}"
    else
        echo -e "${RED}Error: vcpkg.cmake not found at: ${vcpkg_cmake_path}${NC}"
        exit 1
    fi
    echo -e "${BLUE}vcpkg setup completed.${NC}"
}

init_project() {
    echo -e "${BLUE}Initializing project...${NC}"
    check_vcpkg_setup
    vcpkg_path=$(cat "$VCPKG_PATH_FILE")
    echo -e "${YELLOW}Creating build directory...${NC}"
    mkdir -p build
    cd build
    echo -e "${YELLOW}Running CMake...${NC}"
    cmake .. -DCMAKE_TOOLCHAIN_FILE="$vcpkg_path" -DVCPKG_MANIFEST_MODE=ON
    if [ $? -ne 0 ]; then
        echo -e "${RED}Error: CMake configuration failed.${NC}"
        exit 1
    fi
    cd ..
    echo -e "${GREEN}Project initialized successfully.${NC}"
}

reset_project() {
    echo -e "${BLUE}Resetting project...${NC}"
    echo -e "${YELLOW}Removing build directory...${NC}"
    rm -rf build
    echo -e "${YELLOW}Reinitializing project...${NC}"
    init_project
    echo -e "${GREEN}Project reset completed.${NC}"
}

configure_release() {
    echo -e "${BLUE}Configuring project in Release mode...${NC}"
    check_vcpkg_setup
    vcpkg_path=$(cat "$VCPKG_PATH_FILE")
    cd build
    echo -e "${YELLOW}Running CMake in Release mode...${NC}"
    cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_TOOLCHAIN_FILE="$vcpkg_path" -DVCPKG_MANIFEST_MODE=ON ..
    if [ $? -ne 0 ]; then
        echo -e "${RED}Error: CMake configuration in Release mode failed.${NC}"
        exit 1
    fi
    cd ..
    echo -e "${GREEN}Project configured in Release mode.${NC}"
}

configure_debug() {
    echo -e "${BLUE}Configuring project in Debug mode...${NC}"
    check_vcpkg_setup
    vcpkg_path=$(cat "$VCPKG_PATH_FILE")
    cd build
    echo -e "${YELLOW}Running CMake in Debug mode...${NC}"
    cmake -DCMAKE_BUILD_TYPE=Debug -DCMAKE_TOOLCHAIN_FILE="$vcpkg_path" -DVCPKG_MANIFEST_MODE=ON ..
    if [ $? -ne 0 ]; then
        echo -e "${RED}Error: CMake configuration in Debug mode failed.${NC}"
        exit 1
    fi
    cd ..
    echo -e "${GREEN}Project configured in Debug mode.${NC}"
}

build_project() {
    echo -e "${BLUE}Building project...${NC}"
    check_vcpkg_setup
    cd build
    echo -e "${YELLOW}Running CMake build...${NC}"
    cmake --build .
    if [ $? -ne 0 ]; then
        echo -e "${RED}Error: Build failed.${NC}"
        exit 1
    fi
    cd ..
    echo -e "${GREEN}Project build completed.${NC}"
}

test_project() {
    echo -e "${BLUE}Testing project...${NC}"
    check_vcpkg_setup
    cd build || exit 1
    echo -e "${YELLOW}Running CMake build...${NC}"
    cmake --build .
    if [ $? -ne 0 ]; then
        echo -e "${RED}Error: Build failed.${NC}"
        exit 1
    fi
    cd .. || exit 1
    echo -e "${YELLOW}Testing project...${NC}"
    cd build || exit 1
    ctest --rerun-failed --output-on-failure
    if [ $? -ne 0 ]; then
        echo -e "${RED}Error: Testing failed.${NC}"
        exit 1
    fi
    echo -e "${GREEN}Testing project completed.${NC}"
}

clean_project() {
    echo -e "${BLUE}Cleaning project...${NC}"
    echo -e "${YELLOW}Removing testing directory...${NC}"
    rm -rf Testing
    echo -e "${YELLOW}Removing Debug folders in src...${NC}"
    find src -type d -name "Debug" -exec rm -rf {} +
    echo -e "${YELLOW}Removing specific binaries...${NC}"
    rm -rf r-type_client
    rm -rf r-type_server
    rm -rf ./lib/*
    echo -e "${GREEN}Project cleaned successfully.${NC}"
}

run_clang_tidy() {
    echo -e "${BLUE}Running Clang-Tidy...${NC}"
    check_vcpkg_setup
    cd build || exit 1
    echo -e "${YELLOW}Running Clang-Tidy on source files...${NC}"
    cmake --build . --target clang-tidy
    if [ $? -ne 0 ]; then
        echo -e "${RED}Error: Clang-Tidy failed.${NC}"
        exit 1
    fi
    cd ..
    echo -e "${GREEN}Clang-Tidy completed successfully.${NC}"
}

full_build() {
    echo -e "${BLUE}Starting full build process...${NC}"
    setup_vcpkg
    init_project
    configure_release
    build_project
    echo -e "${GREEN}Full build process completed successfully.${NC}"
}

if [ $# -eq 0 ]; then
    echo -e "${RED}Error: No rule specified.${NC}"
    show_help
    exit 1
fi

case $1 in
    setup_vcpkg)
        setup_vcpkg
        ;;
    init)
        init_project
        ;;
    reset)
        reset_project
        ;;
    release)
        configure_release
        ;;
    debug)
        configure_debug
        ;;
    build)
        build_project
        ;;
    test)
        test_project
        ;;
    lint)
        run_clang_tidy
        ;;
    clean)
        clean_project
        ;;
    full_build)
        full_build
        ;;
    help)
        show_help
        ;;
    *)
        echo -e "${RED}Error: Unknown rule '$1'${NC}"
        show_help
        exit 1
        ;;
esac
