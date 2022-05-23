package com.company.factory;

import com.company.containter.Container;
import com.company.utils.ContainerStrategy;

public interface Factory
{
    Container createContainer(ContainerStrategy strategy);
}
