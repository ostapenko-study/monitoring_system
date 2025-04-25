import React from "react";

import NetworkInfo from "./NetworkInfo";

export const NetworkList = ({ items, onConfigure, onTop}) => {
  return (
    <div style={styles.listWrapper}>
      {
        items.map((item, index) =>
           <NetworkInfo 
              data={item}
              onConfigure={onConfigure}
              onTop={onTop}
            />
          )
      }
    </div>
  );
};

const styles = {
  listWrapper: {
    maxWidth: "1200px",
    margin: "2rem auto",
    fontFamily: "sans-serif",
  },
};

export default NetworkList;
