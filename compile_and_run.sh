rm -r Output
mkdir -p Output
c++ CPP_Testing/main.cpp -o CPP_Testing/main -w
cd CPP_Testing
./main
cd ..
python Grapher.py Output/Vector_Random0to100000.csv