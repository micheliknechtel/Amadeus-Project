#!/usr/bin/env python

import sys
import random

if __name__ == '__main__':
    
    if len( sys.argv ) != 7:
        print " *** Usage: ./gen.py <number_of_airports> <density> <min f/od> <max f/od> <max_hops> <alfa_error>"
        print "        Ex: ./gen.py         10             100         1          3          4           2"
        exit(0)

    # parse the args ------------------------------
    V = int(sys.argv[1])
    d = int(sys.argv[2])
    
    min_fod = int(sys.argv[3])
    max_fod = int(sys.argv[4])
    max_hop = int(sys.argv[5])
    alfa_error = int(sys.argv[6])/100.0

    if d != 100:
        print " *** Please use density=100... we are not ready yet to do something else"
        exit(1)

    # Buid The adj Matrix -------------------------    
    #mat = {}
    #for i in xrange(V):
    #    for j in xrange(V):
    #        if i==j: continue
    #        mat[i,j] = 1


    # Prepare the Airport Names -------------------
    AL=[ 'AAA' ]
    for i in xrange( V-1 ):
        tmp = str(AL[i])

        if tmp[2] != 'Z':
            tmp2 = tmp[:2] + chr( ord(tmp[2]) +1 )
            
        if tmp[2] == 'Z' and tmp[1] != 'Z':
            tmp2 = tmp[0] + chr( ord(tmp[1]) +1 ) + 'A'
        
        if tmp[2] == 'Z' and tmp[1] == 'Z':
            tmp2 = chr( ord(tmp[0]) +1 ) + 'AA'
            
        AL.append( tmp2 )


    # Now, Create the OD structure with fulfill xij
    OD = {}
    for i in xrange(V):
        for j in xrange(V):
            if i==j : continue
            OD[i,j] = random.randint(1000,2000)
    

    # OD itineraries - the flights from o to d
    ODI = {}
    
    for i in xrange(V):     # for each OD
        for j in xrange(V):
            if i==j : continue
            n_fod = random.randint(min_fod,max_fod) # chose the number of itineraries
            ODI[i,j] = []
            
            alfa = (1.0) / n_fod
            
            for k in xrange( n_fod ): # Make an Itinerary
                ITI=[i]
                hops = random.randint(1,max_hop)
                
                for w in xrange(hops-2): # Choose an ntermediary Airport
                    h = random.randint( 0, V-1 )
                    while h == i or h == j or h in ITI:
                        h = random.randint( 0, V-1 )

                    ITI.append(h)

                ITI.append(j)
                
                flag=False
                for w in xrange(len(ODI[i,j])): # try to compose the alfas!! (complex!)
                    if ODI[i,j][w][0] == ITI:
                        ODI[i,j][w] = (ITI, alfa+ODI[i,j][w][1])
                        flag = True
                                
                if flag == False:
                    ODI[i,j].append( (ITI, alfa) )
    
    
    #print ODI
    Lphat = {}
      # computing Arrival and Departures
    Arrival = [0 for x in range(V)]
    Departure = [0 for x in range(V)]
    
    #Computing p_hat for each leg    
    for i in xrange(V):  # for each LEG
        for j in xrange(V):
            if i==j : continue
            Lphat[i,j] = 0
    
    for i in xrange(V):  # for each OD
        for j in xrange(V):
            if i==j: continue
            
            for w in ODI[i,j]:
                n = OD[i,j] * w[1]# w[1] = alfa
            
                for k in xrange( len(w[0])-1 ) :# w[0] = ITI = [i,x,y,j] ...
                    lego = w[0][k] #origin
                    legd = w[0][k+1] #destiny
                    Lphat[lego, legd] = Lphat[lego, legd] + n
                    
                    
    for i in xrange(V):  # for each LEG]\
    	for j in xrange(V):
    		if i==j : continue
         	Arrival[j] =  Arrival[j] + Lphat[i,j] 
         	Departure[i] = Departure[i]  + Lphat[i, j]
     	 	print "Lphat[%d, %d]=%g, Arrival[%d]=%g,Departure[%d]=%g\n" % (i, j, Lphat[i, j], j, Arrival[j], i,Departure[i])

    #print Lphat
    
    # computing Arrival and Departures
    

    # Print the Airports File
    f = open('airports.csv', 'w')
    f.write( 'Header\n' )
    for i in xrange(V):
        f.write( '%s,%g,%g\n' % (AL[i],Arrival[i],Departure[i]))
    f.close()
        
    # Print the Legs File
    f = open('legs.csv', 'w')
    for i in xrange(V):  # for each LEG
        for j in xrange(V):
            if i==j: continue
            f.write( '%s,%s,%d,%d,%g,%g,,\n' % (AL[i], AL[j],0.5*Lphat[i,j], Lphat[i,j],(5.0/4)*Lphat[i,j], 1.0 ))
    f.close()
    
    # Print the Itinerary File
    # No header.....
    f = open('itineraries.csv', 'w')
    for i in xrange(V):  # for each OD
        for j in xrange(V):
            if i==j: continue
            
            alfa_list = [ k[1] for k in ODI[i,j]]

            
            for kk in range(len(ODI[i,j])):
                k = ODI[i,j][kk]
                
                ori = AL[k[0][0]]
                dest = AL[k[0][-1]]
                
                c1 = AL[k[0][1]] if len(k[0]) >= 3 else ''
                c2 = AL[k[0][2]] if len(k[0]) >= 4 else ''
                
                #print alfa_list[kk], alfa_error
                f.write( '%s,%s,%s,%s,%g\n' %( ori, c1, c2, dest, alfa_list[kk] ))
    f.close()
    
    
    # Print the Solution File
    # No header.....
    f = open('solution.csv', 'w')
    for i in xrange(V):  # for each OD
        for j in xrange(V):
            if i==j:  OD[i,j]=0;
            f.write(" %g " % (OD[i,j]))
        f.write("\n")
    f.close()
    

