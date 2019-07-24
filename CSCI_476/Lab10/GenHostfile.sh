###############################################################################
# Generate a hostfile for use with MPI and mpirun, etc                        #
#   based on machines that are [actually] available                           #
#=============================================================================#
# Erik Ginter                                                                 #
#   Spring 2015                                                               #
###############################################################################

# The name of our generated hostfile
HOSTFILE=Hosts.txt

# Delete an existing hostfile if it exists #
rm -f $HOSTFILE

# Get the time ( for the generated header )
DATETIME="$(date)"

# Emit the generated header
echo -e "##"                             >> $HOSTFILE
echo -e "# CS Linux Lab hostfile"        >> $HOSTFILE
echo -e "# Generated by GenHostfile.sh"  >> $HOSTFILE
echo -e "#   on $DATETIME"               >> $HOSTFILE
echo -e "##"                             >> $HOSTFILE
echo -e ""                               >> $HOSTFILE

## EDIT THIS IF THE LINUX LAB CHANGES ##
HOSTS=(
    "boole"
    "brooks"
    "cook"
    "denning"
    "dijkstra"
    "floyd"
    "hoare"
    "hopper"
    "iverson"
    "knuth"
    "liskov"
    "lovelace"
    "mccarthy"
    "minsky"
    "newell"
    "parnas"
    "perlis"
    "rabin"
    "ritchie"
    "shaw"
    "simon"
    "tarjan"
    "thompson"
    "turing"
    "wilkes"
    "wirth"
    "vonneumann"
)

## Set this to non-0 if you want to see the ping output
BE_QUIET=0

## The number of pings to send
PINGS=2

TIMEOUT=60

## Go over each host, checking for availability
echo "Checking available hosts... ( This may take some time )"
for host in "${HOSTS[@]}"
do
    # Change our command if we don't want the output
    # YES, THERE IS PROBABLY A BETTER WAY TO DO THIS
    # NO, I DON'T KNOW HOW TO DO IT
    if [ $BE_QUIET -eq 0 ]
    then
	ssh -o ConnectTimeout=$TIMEOUT -q $USER@$host exit
	##ping -q -c $PINGS $host 1>/dev/null 2>/dev/null
    else
	##ping -c $PINGS $host
	ssh -o ConnectTimeout=$TIMEOUT $USER@$host exit
    fi

    # Did the ping succeed?
    #   If it did, write it out to the hostfile
    if [ $? -eq 0 ]
    then
	echo -e "$host slots=1" >> $HOSTFILE
    else
	echo "Host $host is down. ( Skipping )"
	echo -e "\t#$host is down" >> $HOSTFILE
    fi
done
echo "Done!"