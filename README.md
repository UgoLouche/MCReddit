# MCReddit

This is a Reddit based Monte Carlo Text Generator. More precisely, this program will fetch all self-posts of a given subreddit over a fixed time window, then train a Monte Carlo Text generator from that data. 

Use reddit CREST API with the Casablanca C++ CREST API. Monte Carlo Text generator implementation is my own and probably less than optimal. 

Finally, everything is handled through text files so don't expect any big-data technology like distributed RDD and such or even a fine memory management. To be clear, this program will kill your RAM and swap. Parsing 6 months of the Life Is Strange subreddit took me more than 20Go of RAM. Here's a selection of [the result](https://www.reddit.com/r/lifeisstrange/comments/4u09v4/ep5_spoilersi_trained_a_markov_chain_text/?ref=share&ref_source=link).

#####Technical Details
- No configuration file per se but you can tweak conf.h to change the subreddit, time window, ngram size, max post size and number of posts produced
- The Reddit Parse phase and train phase are distinct and can be executed independently, the switches controlling that are in MCReddit.cpp lines 25 and 26.
- By default the Ngram size is 15, which is pretty big but seems to work well in the case of Reddit where writing style is inconsistent.
- There are a *start* and *end* Ngrams defined so the program will also learn when to finish posts. Because of this, by default it will produce 100 posts rather than a fixed number of Ngram. You can change that in conf.h.
- This is a visual studio project, you should open it through the VS project file included
- Casablanca CREST API included so it *should* compile directly from the repository in Visual Studio. It might re-download some of the package files automatically though. 
- Some reddit parses (as well as a copy of Alice in wonderland) and output samples are included in the 'samples' folder for convenience. 
- The NgramNode class is basically a tree structure of depth *NgramSize* and degree 255 so you can access any arbitrary Ngram in constant time O('NgramSize'). It is coupled with an array referencing all created Ngram for when iterating through all Ngram is needed. 


###TODO
- cleaner sample folder, rename files
- Proper configuration files, clean-up code
- Change the configured subreddit for something more general like r/philosophy
