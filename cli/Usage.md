# myquantumkey

See Readme [here](../README.md)

## How to run myquantumkey 

myquantumkey has 3 functions:
- Create myquantumkey 
- Create proof 
- Verify myquantumkey proof 

### Create myquantumkey

Perform the following:

1. Think of a secret (between 20 to 50 characters)
2. Use the executable "myquantumkey\_create.exe" to calculate myquantumkey: 

```
myquantumkey\_create.exe <secret>
```

The output will be something like:

```
myquantumkey value of secret is:2bb80d537b1da3e38bd30361aa855686bde0eacd7162fef6a25fe97bf527a25b
```

3. Copy the value of myquantumkey and create a TEXT record in the ENS:
 - go to https://app.ens.domains/&lt;ENS name&gt; 
 - choose "edit profile" and add the TEXT record with key = myquantumkey and value = &lt;value of myquantumkey&gt;
 - it should look like ![image](ENS_TEXT.png =200x)

### Create proof

In order to prove that you know your myquantumkey, you first will receive a "challenge" from the verifier. Perform the following:

1. Use the executable "myquantumkey\_create.exe" to create the proof. Assuming that the challenge is "abcdef" (up to 16 characters): 

```
myquantumkey\_create.exe <secret> abcdef
```

The output will be something like:

```
myquantumkey value of secret is:2bb80d537b1da3e38bd30361aa855686bde0eacd7162fef6a25fe97bf527a25b
Proof output to file abcdef_136.zkmpc
```

2. Copy the file "abcdef\_136.zkmpc" to be provided as proof of knowledge of &lt;secret&gt;

### Verify myquantumkey proof

Assuming that you are trying to verify if &lt;ENS name&gt; is really who he/she claims he/she is, and knows the &lt;secret&gt; used to create myquantumkey,

1. Use the executable "myquantumkey\_verify.exe" to create the proof. Assuming that the challenge is "abcdef" (up to 16 characters), and the ENS name is "quantum.eth": 

```
myquantumkey_verify.exe `node getText.mjs quantum.eth` abcdef abcdef_136.zkmp
```

2. The output will be "Proof for hash: Proof verified ok" if it is ok.


