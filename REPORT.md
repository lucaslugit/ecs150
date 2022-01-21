# Introduction

This is a report about the shell project. The main purpose of the shell is  of user-supplied commands 
with optional arguments

 - Execution command
 - Redirection to file
 - piping

# User Input

When user input, we will use fgets() to save command in the variable cmd. Then, we will separate all the commands into a single word. We will use these single words when we want to execute commands. For example, During redirection, the command is like "echo Hello World > file". We can see, when we want to execute this function, we need to find operator ">" to let sshell know, the user wants to redirect. So we can see the important of separate commands in a single word. It can help us to locate what the user wants. 

# Execuate
When we want to execute the command, we need to analyze user input. After we analyzed it, we need to use code in sshell.c to execute it. We can still use the same example as before. After sshell see the operator ">", it knows we need to save the words before ">" to the file after ">". So we can use the words saved in array args[] to execute it. First, we save the string before ">" to char array content. Then, we use the same way to treat the name of the file. We save the name of the file to a variable file. After that, we open the file and save content to the file. 

# Test
During the test, we meet some easy or difficult bugs. The easy bugs are easy to fix, but the difficult bugs need to spend lots of time. We meet these difficult bugs are because we did not understand some background of these bugs sometimes. Or we understand this background but we did not understand the warning or error of the bug. Sometimes, it only shows us segmentation faults, so it is difficult to fix. One of the bugs we still have not fixed is phase 4. We finished phase 4 and test it on the CSIF environment, everything is good. The content can write in the file and the file can open successfully, after the file opens, we can see the content is the same as we entered. However, phase 4 can pass none of the tests. It shows a segmentation fault, and we still do not know why since it shows success on our CSIF computer. We want to try more and test more, but the time is not enough, so we choose to comment whole phase 4 in our code and treat it as a pity. 

## Conclusion
From this project, the most helpful thing is coding with high-quality and established industry standards. Our coding become more organized. The comment also helps my partner to understand my code. When I want to review the code I wrote before, it is difficult to understand it although it is written by me. But now, I think it will not be that difficult to read with my organized code and comment. 

