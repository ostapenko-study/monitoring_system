#!/bin/bash
set -e


echo "[INFO] Чищу старі білди..."
rm -rf src/build src/dist
mkdir -p src/build src/dist

# Будуємо контейнер
docker build -t monitoring-builder .

# Запускаємо збірку
docker run --rm -it -v $(pwd)/src:/workspace/src monitoring-builder bash -c "
    cd /workspace/src &&
    mkdir -p build &&
    cd build &&
    qmake ../monitoring_system.pro &&
    make -j\$(nproc)

    # Створюємо .desktop файли і обробляємо їх linuxdeployqt
    for app in agent proxy sender server; do
        echo \"[Desktop Entry]
Name=\$app
Exec=\$app
Icon=\$app
Type=Application
Categories=Utility;\" > \$app.desktop

        linuxdeployqt \$app.desktop -appimage
    done
"

echo ""
echo "✅ Готово! Файли зібрані в src/build/"

mkdir -p /src/dist

# копіюємо всі бінарники
cp src/build/agent/agent src/dist/
cp src/build/proxy/proxy src/dist/
cp src/build/sender/sender src/dist/
cp src/build/server/server src/dist/


echo "✅ Готово! скопійовано в /src/dist/"