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
-	A hash performed using Keccak256 on a randomly generated secret pre-image values of size larger than 256 bits is resistant against quantum cryptanalysis.
-	There exists a quantum-safe context-sensitive zero-knowledge proof system that wallet owners can use in the future to prove knowledge of the secret pre-image of a Keccak256 hash.
-	After post-quantum migration, authentication of classical walletaddresses will require both the digital signature as well as a zero-knowledge proof of the secret.

## Solution
1)	Create a “myquantumkey” smartcontract that has the following methods:
 - CreateKey: called by wallet owner to submit the key verification blob
 - ConfirmKey: called by wallet onwer in a subsequent Epoch to confirm the key verification blob 
 - StopConfirmKey: to prevent ConfirmKey from being called. Can only be called by owner before quantum computers are powerful enough.
 - RetrieveKey: called by any method to retrieve the key verification blob

2)	Create a “myquantumkey” front-end app to perform the following:
 - “CreateKey”: to allow wallet owner to submit the key verification blob
 - “ConfirmKey”: to allow walllet owner to confirm the key verification blob
 - “CheckKey”: to allow anyone to retrieve the key verification blob for user verification

##	Threat model
o	Attacker attempts to perform an unauthorized CreateKey or ConfirmKey.
 -	Not possible since Attacker does not have wallet key to sign the transaction
o	Attacker attempts to retrieve the secret from ConfirmKey
 -	Not possible since Keccak256 cannot be reversed
o	Attacker attempts to impersonate as wallet owner after using a quantum computer to find the wallet private key
 -	Not possible since Attacker does not know the secret, and cannot present the zero-knowledge proof of the secret
