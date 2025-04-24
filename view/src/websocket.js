import React, { useState, useCallback, useEffect } from 'react';
import useWebSocket, { ReadyState } from 'react-use-websocket';

import SourceView from './views/SourceView'

export const WebSocketDemo = () => {
  const [socketUrl, setSocketUrl] = useState('ws://localhost:8002');
//   const [messageHistory, setMessageHistory] =
//     useState < MessageEvent < any > [] > [];

  const { sendMessage, lastMessage, readyState } = useWebSocket(socketUrl, {
    shouldReconnect: (closeEvent) => true,
  });

  const [mainData, setMainData]  = useState(new Map())

  useEffect(() => {
    if (lastMessage !== null) {
        const newMainData = mainData ? mainData : new Map()
        const parsed = JSON.parse(lastMessage.data)
        newMainData.set(parsed["id"], parsed)
        setMainData(newMainData)
    }
  }, [lastMessage]);

  const connectionStatus = {
    [ReadyState.CONNECTING]: 'Connecting',
    [ReadyState.OPEN]: 'Open',
    [ReadyState.CLOSING]: 'Closing',
    [ReadyState.CLOSED]: 'Closed',
    [ReadyState.UNINSTANTIATED]: 'Uninstantiated',
  }[readyState];

  return (
    <div>
      <div>The WebSocket is currently {connectionStatus}</div>
      {mainData ? mainData.keys().map((index) => <SourceView key={index} data={mainData.get(index)} />) : null}
    </div>
  );
};

export default WebSocketDemo;