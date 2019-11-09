set -e
#set -x

# Get files if needed.
echo ""
file_list="OR_GLM-L2-LCFA_G17_s20192692359400_e20192700000000_c20192700000028.nc"
echo "Checking for GLM test file $file_list"
for f1 in $file_list
do
    if ! test -f $f1; then
	echo "Getting GLM test file $f1"
	wget https://github.com/edhartnett/data_using_netcdf/blob/master/GOES/GOES-17/GLM/${f1}?raw=true
	mv ${f1}?raw=true ${f1}
    fi
done

# Run the test.
./tst_glm_read -v
./tst_glm_read_arrays -v

