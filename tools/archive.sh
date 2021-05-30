echo "Making zip image..."
zip dist/pidi-os-image.zip dist/os-image.bin
echo "Making tar image..."
tar -cvf dist/pidi-os-image.tar dist/os-image.bin
