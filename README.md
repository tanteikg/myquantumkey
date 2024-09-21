# myquantumkey
Register a key that can be used in the quantum future to authenticate yourself

## Problem
-	In the future, quantum computers will compromise existing public key cryptosystems. This requires a migration of the cryptosystem which involves changing the cryptosystem and all the users’ public and private keys. How this migration will happen is still undecided.
-	Applications such as blockchains use public key cryptography for user and transaction authentication. It also uses public key cryptography for user identification. E.g. The wallet address is the hash(public key). 
-	Currently, proof of ownership of a wallet address is achieved when the user creates a digital signature using the private key associated with the public key.
-	When quantum computers come, users will lose the ability to prove this address ownership since attackers can also create the same digital signing proof. 
-	We need to create a quantum-safe method so that existing wallet owners can still perform a proof of ownership in the future after the migration.

## Assumptions
-	Currently, besides the wallet owner, no other persons/attackers can create a valid digital signature corresponding to the wallet address
-	A hash performed using SHA256 on a randomly generated secret pre-image values of size larger than 256 bits is resistant against quantum cryptanalysis.
-	There exists a quantum-safe context-sensitive zero-knowledge proof system that wallet owners can use in the future to prove knowledge of the secret pre-image of a SHA256 hash.
-	After post-quantum migration, authentication of classical walletaddresses will require both the digital signature as well as a zero-knowledge proof of the secret.

## Solution
1) Think of a secret (should be long)
   
2)	What we want is to create a ENS TEXT record with key "myquantumkey" that stores the text which should be created based on SHA256(secret)
   
3)	To build a front-end app "myquantumkey" to perform the following
 - “CreateENSRecord”: to allow wallet owner to create the text record.
    -- UPDATE: this function is not needed as it is already provided by https://app.ens.domains/
 - “CheckKey”: to allow anyone to retrieve the key verification blob for user verification
 - "CreateProof" : to allow owner to proof knowledge of key without revealing key 

## Threat model
- 	Attacker attempts to perform an unauthorized record creation.
   --	Not possible since Attacker does not have wallet key to sign the transaction
-	 Attacker attempts to retrieve the secret from TEXT record
   --	Not possible since Keccak256 cannot be reversed
-	Attacker attempts to impersonate as wallet owner after using a quantum computer to find the wallet private key
  --	Not possible since Attacker does not know the secret, and cannot present the zero-knowledge proof of the secret

## installation 

note: only tested on WSL2 running on Windows (i.e. Linux on Windows)

```
git clone https://github.com/tanteikg/myquantumkey
cd cli/ZKBoo/MPC_SHA256
make
cd ../..
```

if you list the directory, you will see the following files:
- Usage.md (how to use)
- getText.mjs 
- myquantumkey\_create.exe
- myquantumkey\_create.exe

Please follow the usage [here](cli/Usage.md) on how use 


