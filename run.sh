if [[ $1 == "-c" ]]
then
    make clean
    exit 0
fi

make create_dirs
make

./build/apps/main

source venv/bin/activate
cd src/
python3 plotResults.py
deactivate

xdg-open scala_log.png
xdg-open scala_normale.png

cd ..

exit 0