TARGETS: ../myquantumkey_create.exe ../myquantumkey_verify.exe 

../myquantumkey_create.exe: MPC_SHA256.c shared.h
	gcc -fopenmp MPC_SHA256.c -o ../myquantumkey_create.exe -lssl -lcrypto

../myquantumkey_verify.exe: MPC_SHA256_VERIFIER.c shared.h
	gcc -fopenmp MPC_SHA256_VERIFIER.c -o ../myquantumkey_verify.exe -lssl -lcrypto
