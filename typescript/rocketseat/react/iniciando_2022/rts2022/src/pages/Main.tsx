import { useState } from "react";
import { Tweet } from "../components/Tweet";

export function Main()
{
  const [tweets, setTweet] = useState<string[]>(["Tweet 1"]);

  function createTweet()
  {
      setTweet(tweets.concat(["Tweet " + (tweets.length + 1)]));
  }

  return (
      <div>
        {tweets.map((t, i) => <Tweet key={i} text={t} />)}

        <button onClick={createTweet} >Add Tweet</button>
      </div>
  );
}