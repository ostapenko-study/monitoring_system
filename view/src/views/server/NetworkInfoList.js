import React from "react";

import NetworkInfo from "./NetworkInfo";

export const NetworkList = ({ items, onOpenAddressWorker}) => {
  return (
    <div style={styles.listWrapper}>
      {
        items
        .slice()
        .sort((a, b) => b.name.localeCompare(a.name))
        .map((item, index) =>
           <NetworkInfo 
              data={item}
              onOpenAddressWorker={onOpenAddressWorker}
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
