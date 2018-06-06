rm -r Output
mkdir -p Output
cd CPP_Testing
for ((i = 0; i < 20; i++)); do ./main; done
cd ..