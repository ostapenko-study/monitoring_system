import React, { useState, useCallback, useEffect } from 'react';
import useWebSocket, { ReadyState } from 'react-use-websocket';

import SourceView from './views/SourceView'
import NoConnection from './views/NoConnection';
import ServerManager from './views/server/ServerManager';

function getRandomInt(min, max) {
  return Math.floor(Math.random() * (max - min + 1)) + min;
}

export const WebSocketDemo = () => {
  const [socketUrl, setSocketUrl] = useState('ws://localhost:8020');

  const { sendMessage, lastMessage, readyState } = useWebSocket(socketUrl, {
    shouldReconnect: (closeEvent) => true,
  });

  const sendMessageWrapper = (pkg) => {
    pkg.key = "view";
    pkg.role = "view";
    pkg.index = getRandomInt(1, 10000000)
    sendMessage(JSON.stringify(pkg));
  };

  const [mainData, setMainData]  = useState(new Map())

  const [viewDataResponse, setViewDataResponse]  = useState({})
  useEffect(() => {
    if (lastMessage !== null) {
        const parsed = JSON.parse(lastMessage.data)
        if(parsed.role == "view"){
          setViewDataResponse(parsed)
        }else{
          const newMainData = mainData ? mainData : new Map()
          newMainData.set(parsed["id"], parsed)
          setMainData(newMainData)  
        }
    }
  }, [lastMessage]);

  const connectionStatus = {
    [ReadyState.CONNECTING]: 'Connecting',
    [ReadyState.OPEN]: 'Open',
    [ReadyState.CLOSING]: 'Closing',
    [ReadyState.CLOSED]: 'Closed',
    [ReadyState.UNINSTANTIATED]: 'Uninstantiated',
  }[readyState];

  console.log(viewDataResponse)

  return (
    <div>
      <div>The WebSocket is currently {connectionStatus}</div>
      {
        readyState == ReadyState.OPEN
        ?
        <div>
          <ServerManager sendMessage={sendMessageWrapper} lastResponse={viewDataResponse}/>
          {mainData ? mainData.keys().map((index) => <SourceView key={index} data={mainData.get(index)} />) : null}
        </div>
        :
        <NoConnection url={socketUrl}/>
      }
    </div>
  );
};

export default WebSocketDemo;